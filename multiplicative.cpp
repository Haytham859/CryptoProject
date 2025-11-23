#include "multiplicative.h"

// الدوال المحلية للملف
static int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

QString multiplicativeEncrypt(const QString &text, int key) {
    if (gcd(key, 26) != 1) return "Error: Key not coprime with 26!";
    QString result;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int val = ((c.unicode() - base.unicode()) * key) % 26;
            result.append(QChar(val + base.unicode()));
        } else result.append(c);
    }
    return result;
}

QString multiplicativeDecrypt(const QString &text, int key) {
    int inv = modInverse(key, 26);
    if (inv == -1) return "Error: No modular inverse for key!";
    QString result;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int val = ((c.unicode() - base.unicode()) * inv) % 26;
            if (val < 0) val += 26;
            result.append(QChar(val + base.unicode()));
        } else result.append(c);
    }
    return result;
}
