#include "autokey.h"

QString autokeyEncrypt(const QString &text, const QString &key) {
    QString result;
    QString k = key.toUpper();
    QString msg = text.toUpper();
    int j=0;
    for (QChar c : msg) {
        if (c.isLetter()) {
            int shift = k[j].unicode() - 'A';
            result.append(QChar((c.unicode()-'A'+shift)%26 + 'A'));
            k += c;
            j++;
        } else result.append(c);
    }
    return result;
}

QString autokeyDecrypt(const QString &text, const QString &key) {
    QString result;
    QString k = key.toUpper();
    QString msg = text.toUpper();
    int j=0;
    for (QChar c : msg) {
        if (c.isLetter()) {
            int shift = k[j].unicode() - 'A';
            QChar dec = QChar((c.unicode()-'A'-shift+26)%26 + 'A');
            result.append(dec);
            k += dec;
            j++;
        } else result.append(c);
    }
    return result;
}
