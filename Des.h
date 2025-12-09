#ifndef DES_H
#define DES_H
#include <QString>

QString desEncryptText(const QString &plainText, const QString &keyHex);
QString desDecryptText(const QString &cipherHex, const QString &keyHex);

// توليد مفتاح DES عشوائي بصيغة HEX
QString generateDESKeyHex();

#endif // DES_H
