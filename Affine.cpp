#include "affine.h"

// دوال مساعدة محلية للملف
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

QString affineEncrypt(const QString &text, int a, int b) {
    if (gcd(a, 26) != 1){
        QMessageBox::warning(nullptr,"ERROR","'a' must be coprime with 26!");
        return " ";
    }

    QString result;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int val = mathMod(a * (c.unicode() - base.unicode()) + b, 26);
            result.append(QChar(val + base.unicode()));
        } else result.append(c);
    }
    return result;
}

QString affineDecrypt(const QString &text, int a, int b) {
    int inv = modInverse(a, 26);
    if (inv == -1) {
            QMessageBox::warning(nullptr, "Error", "No modular inverse for 'a'!");
            return "";
        }
    QString result;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int val = mathMod(inv * ((c.unicode() - base.unicode()) - b), 26);
            result.append(QChar(val + base.unicode()));
        } else result.append(c);
    }
    return result;
}
