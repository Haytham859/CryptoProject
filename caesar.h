#ifndef CAESAR_H
#define CAESAR_H

#include <QString>

QString caesarEncrypt(const QString &text, int key);
QString caesarDecrypt(const QString &text, int key);

#endif
