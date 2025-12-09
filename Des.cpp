#include "des.h"
#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <vector>
#include <cstdint>

// ===================== Odd Parity Helper ===================
static uint8_t setOddParity(uint8_t b) {
    int ones = 0;
    for (int i = 1; i < 8; ++i) {
        if ((b >> i) & 1) ones++;
    }
    if ((ones % 2) == 0) b |= 0x01;
    else b &= 0xFE;
    return b;
}

// توليد 8 بايت مفتاح DES مع odd parity
static QByteArray generateDESKeyBytes() {
    QByteArray k;
    k.reserve(8);
    for (int i = 0; i < 8; i++) {
        uint8_t b = QRandomGenerator::global()->generate() & 0xFF;
        b = setOddParity(b);
        k.append(char(b));
    }
    return k;
}

// توليد مفتاح DES بصيغة HEX لعرضه للمستخدم
QString generateDESKeyHex() {
    return generateDESKeyBytes().toHex().toUpper();
}

// تحويل HEX → uint64
static uint64_t keyFromHex(const QString &hex) {
    QByteArray k = QByteArray::fromHex(hex.toUtf8());
    if (k.size() != 8) return 0;

    uint64_t v = 0;
    for (int i = 0; i < 8; i++)
        v = (v << 8) | (unsigned char)k[i];
    return v;
}

// ===================== Padding ============================
static QByteArray addPadding(QByteArray data) {
    int pad = 8 - (data.size() % 8);
    for (int i = 0; i < pad; i++) data.append(char(pad));
    return data;
}
static QByteArray removePadding(QByteArray data) {
    if (data.isEmpty()) return data;
    int pad = (unsigned char)data.back();
    if (pad < 1 || pad > 8) return data;
    data.chop(pad);
    return data;
}

// ===================== Block Conversions ===================
static uint64_t bytesToBlock(const QByteArray &b) {
    uint64_t x = 0;
    for (int i = 0; i < 8; i++)
        x = (x << 8) | (unsigned char)b[i];
    return x;
}
static QByteArray blockToBytes(uint64_t x) {
    QByteArray b;
    for (int i = 7; i >= 0; i--)
        b.append(char((x >> (i*8)) & 0xFF));
    return b;
}

// ===================== Bit Helpers ========================
static int getBit(uint64_t val, int pos, int totalBits) {
    return (val >> (totalBits - pos)) & 1ULL;
}
static void setBit(uint64_t &val, int pos, int bit, int totalBits) {
    if (bit)
        val |= (1ULL << (totalBits - pos));
    else
        val &= ~(1ULL << (totalBits - pos));
}
static uint64_t permute(uint64_t in,const int *tb,int inBits,int outBits) {
    uint64_t o = 0;
    for (int i = 0; i < outBits; i++) {
        int src = tb[i];
        int b = getBit(in, src, inBits);
        setBit(o, i+1, b, outBits);
    }
    return o;
}

// ===================== DES Tables =========================
static const int IP[64] = {
    58,50,42,34,26,18,10,2, 60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6, 64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,  59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5, 63,55,47,39,31,23,15,7
};
static const int FP[64] = {
    40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
};
static const int E[48] = {
    32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,
    12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,
    24,25,26,27,28,29,28,29,30,31,32,1
};
static const int P[32] = {
    16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
};
static const int PC1[56] = {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,21,13,5,28,20,12,4
};
static const int PC2[48] = {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
};
static const int SHIFTS[16] = {
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

// S-boxes
static const int SBOX[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// ===================== Feistel =============================
static uint32_t feistel(uint32_t R, uint64_t sk) {
    uint64_t ER = permute(R, E, 32, 48);
    uint64_t x = ER ^ sk;
    uint32_t out = 0;

    for (int i = 0; i < 8; i++) {
        int shift = (7 - i) * 6;
        int six = (x >> shift) & 0x3F;
        int row = ((six & 0x20) >> 4) | (six & 1);
        int col = (six >> 1) & 0xF;
        int s = SBOX[i][row][col];
        out = (out << 4) | s;
    }
    return permute(out, P, 32, 32);
}

// ===================== Subkeys =============================
static std::vector<uint64_t> generateKeys(uint64_t key64) {
    uint64_t key56 = permute(key64, PC1, 64, 56);
    uint32_t C = (key56 >> 28) & 0xFFFFFFF;
    uint32_t D = key56 & 0xFFFFFFF;

    std::vector<uint64_t> out(16);
    for (int i = 0; i < 16; i++) {
        C = ((C << SHIFTS[i]) | (C >> (28 - SHIFTS[i]))) & 0xFFFFFFF;
        D = ((D << SHIFTS[i]) | (D >> (28 - SHIFTS[i]))) & 0xFFFFFFF;
        uint64_t CD = ((uint64_t)C << 28) | D;
        out[i] = permute(CD, PC2, 56, 48);
    }
    return out;
}

// ===================== DES Core ============================
static uint64_t desCore(uint64_t block, uint64_t key, bool enc) {
    auto keys = generateKeys(key);
    uint64_t ip = permute(block, IP, 64, 64);

    uint32_t L = ip >> 32;
    uint32_t R = ip & 0xFFFFFFFF;

    for (int i = 0; i < 16; i++) {
        uint64_t k = enc ? keys[i] : keys[15 - i];
        uint32_t newR = L ^ feistel(R, k);
        L = R;
        R = newR;
    }

    uint64_t pre = ((uint64_t)R << 32) | L;
    return permute(pre, FP, 64, 64);
}

// ===================== Encrypt =============================
QString desEncryptText(const QString &plainText,
                       const QString &keyHex)
{
    QByteArray data = plainText.toUtf8();
    data = addPadding(data);

    uint64_t key = keyFromHex(keyHex);
    QByteArray out;

    for (int i = 0; i < data.size(); i += 8) {
        uint64_t p = bytesToBlock(data.mid(i, 8));
        uint64_t c = desCore(p, key, true);
        out.append(blockToBytes(c));
    }
    return out.toHex().toUpper();
}

// ===================== Decrypt =============================
QString desDecryptText(const QString &cipherHex,
                       const QString &keyHex)
{
    QByteArray data = QByteArray::fromHex(cipherHex.toUtf8());
    uint64_t key = keyFromHex(keyHex);
    QByteArray out;

    for (int i = 0; i < data.size(); i += 8) {
        uint64_t c = bytesToBlock(data.mid(i, 8));
        uint64_t p = desCore(c, key, false);
        out.append(blockToBytes(p));
    }

    return QString::fromUtf8(removePadding(out));
}
