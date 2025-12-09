#include "vigenere.h"

QString vigenereEncrypt(const QString &text, const QString &key) {
    QString result;
    int keyIndex = 0;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int k = key[keyIndex % key.length()].toUpper().unicode() - 'A';
            int val = (c.unicode() - base.unicode() + k) % 26;
            result.append(QChar(val + base.unicode()));
            keyIndex++;
        } else result.append(c);
    }
    return result;
}

QString vigenereDecrypt(const QString &text, const QString &key) {
    QString result;
    int keyIndex = 0;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            int k = key[keyIndex % key.length()].toUpper().unicode() - 'A';
            int val = (c.unicode() - base.unicode() - k + 26) % 26;
            result.append(QChar(val + base.unicode()));
            keyIndex++;
        } else result.append(c);
    }
    return result;
}
