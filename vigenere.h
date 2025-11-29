#ifndef VIGENERE_H
#define VIGENERE_H

#include <QString>
#include <QMessageBox>

QString vigenereEncrypt(const QString &text, const QString &key);
QString vigenereDecrypt(const QString &text, const QString &key);

#endif
