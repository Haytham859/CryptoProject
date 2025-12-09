#ifndef VERNAM_H
#define VERNAM_H

#include <QString>

QString vernamEncrypt(const QString &text, const QString &key);
QString vernamDecrypt(const QString &text, const QString &key);

#endif // VERNAM_H
