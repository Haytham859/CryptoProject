#ifndef AFFINE_H
#define AFFINE_H

#include <QString>
#include <QMessageBox>

QString affineEncrypt(const QString &text, int a, int b);
QString affineDecrypt(const QString &text, int a, int b);

#endif // AFFINE_H
