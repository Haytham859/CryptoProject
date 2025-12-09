#include "caesar.h"

QString caesarEncrypt(const QString &text, int key) {
    QString result;
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar base = c.isUpper() ? 'A' : 'a';
            result.append(QChar((c.unicode() - base.unicode() + key) % 26 + base.unicode()));
        } else result.append(c);
    }
    return result;
}

QString caesarDecrypt(const QString &text, int key) {
    return caesarEncrypt(text, 26 - (key % 26));
}
