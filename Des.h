#ifndef DES_H
#define DES_H
#include <QString>

QString desEncryptText(const QString &plainText, const QString &keyText);
QString desDecryptText(const QString &cipherHex, const QString &keyText);

#endif // DES_H
