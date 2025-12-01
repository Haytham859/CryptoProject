#ifndef MULTIPLICATIVE_H
#define MULTIPLICATIVE_H

#include <QString>
#include <QMessageBox>

QString multiplicativeEncrypt(const QString &text, int key);
QString multiplicativeDecrypt(const QString &text, int key);

#endif // MULTIPLICATIVE_H
