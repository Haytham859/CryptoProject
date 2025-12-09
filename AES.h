#ifndef AES_H
#define AES_H

#include <QString>

QString aesEncryptText(const QString &plainText, const QString &keyText);
QString aesDecryptText(const QString &cipherHex, const QString &keyText);

#endif // AES_H
