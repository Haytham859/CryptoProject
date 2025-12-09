#include "vernam.h"

QString vernamEncrypt(const QString &text, const QString &key) {
    QString result;
    int n = key.length();
    for (int i=0; i<text.length(); ++i) {
        if (text[i].isLetter()) {
            QChar base = text[i].isUpper() ? 'A' : 'a';
            int k = key[i % n].toUpper().unicode() - 'A';
            result.append(QChar(((text[i].unicode()-base.unicode()) ^ k) + base.unicode()));
        } else result.append(text[i]);
    }
    return result;
}

QString vernamDecrypt(const QString &text, const QString &key) {
    return vernamEncrypt(text,key); // Symmetric
}
