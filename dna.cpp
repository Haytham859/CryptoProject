#include "dna.h"
#include <bitset>

static QString textToBin(QString text) {
    QString binaryString = "";
    for (QChar c : text) {
        std::bitset<8> bits(c.toLatin1());
        binaryString += QString::fromStdString(bits.to_string());
    }
    return binaryString;
}

static QString binToText(QString binaryString) {
    QString text = "";
    for (int i = 0; i < binaryString.length(); i += 8) {
        if (i + 8 > binaryString.length()) break;

        QString byteStr = binaryString.mid(i, 8);
        bool ok;
        char c = static_cast<char>(byteStr.toInt(&ok, 2));
        text += c;
    }
    return text;
}

static QString xorOperation(QString textBin, QString keyBin) {
    QString result = "";

    for (int i = 0; i < textBin.length(); i++) {
        QChar kBit = keyBin[i % keyBin.length()];
        QChar tBit = textBin[i];

        if (tBit == kBit) result += '0';
        else result += '1';
    }
    return result;
}

static QString binToDna(QString binaryString) {
    QString dna = "";
        for (int i = 0; i < binaryString.length(); i += 2) {
        QString pair = binaryString.mid(i, 2);
        if (pair == "00") dna += 'A';
        else if (pair == "01") dna += 'T';
        else if (pair == "10") dna += 'C';
        else if (pair == "11") dna += 'G';
    }
    return dna;
}

static QString dnaToBin(QString dna) {
    QString binaryString = "";
    for (QChar c : dna) {
        if (c == 'A') binaryString += "00";
        else if (c == 'T') binaryString += "01";
        else if (c == 'C') binaryString += "10";
        else if (c == 'G') binaryString += "11";
    }
    return binaryString;
}

QString dnaEncrypt(QString text, QString key) {

    key=key.toUpper();

    QString textBits = textToBin(text);
    QString keyBits = textToBin(key);

    QString cipherBits = xorOperation(textBits, keyBits);

    return binToDna(cipherBits);
}

QString dnaDecrypt(QString text, QString key) {

    key=key.toUpper();

    QString cipherBits = dnaToBin(text);

    QString keyBits = textToBin(key);

    QString plainBits = xorOperation(cipherBits, keyBits);

    return binToText(plainBits);

}
