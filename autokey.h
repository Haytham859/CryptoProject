#ifndef AUTOKEY_H
#define AUTOKEY_H

#include <QString>

QString autokeyEncrypt(const QString &text, const QString &key);
QString autokeyDecrypt(const QString &text, const QString &key);

#endif // AUTOKEY_H
