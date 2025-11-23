#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

#include <QString>
#include <QVector>

// Rail Fence
QString railFenceEncrypt(const QString &text, int key);
QString railFenceDecrypt(const QString &text, int key);

// Columnar
QString columnarEncrypt(const QString &text, const QString &key);
QString columnarDecrypt(const QString &text, const QString &key);

// Row Transposition
QString rowTranspositionEncrypt(const QString &text, const QString &key);
QString rowTranspositionDecrypt(const QString &text, const QString &key);

#endif // TRANSPOSITION_H
