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

static int mathMod(int a, int b) {
    return (a % b + b) % b;
}

QString multiplicativeEncrypt(const QString &text, int key) {
    if (gcd(key, 26) != 1) {
        QMessageBox::warning(nullptr,"ERROR","Key not coprime with 26!");
        return " ";
    }
    QString result;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int val = ((c.unicode() - base.unicode()) * key);
            val = mathMod(val, 26);
            result.append(QChar(val + base.unicode()));
        } else result.append(c);
    }
    return result;
}

QString multiplicativeDecrypt(const QString &text, int key) {
    int inv = modInverse(key, 26);

    if (inv == -1){
        QMessageBox::warning(nullptr,"ERROR","No modular inverse for key!");
        return " ";
    }

    QString result;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int val = ((c.unicode() - base.unicode()) * inv);
            val = mathMod(val,26);
            result.append(QChar(val + base.unicode()));
        } else result.append(c);
    }
    return result;
}
