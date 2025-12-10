#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

#include <QString>
#include <QVector>

// Row Transposition
QString rowTranspositionEncrypt(const QString &text, const QString &key);
QString rowTranspositionDecrypt(const QString &text, const QString &key);

#endif // TRANSPOSITION_H
