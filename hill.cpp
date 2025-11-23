#include "hill.h"
#include <QVector>

QVector<QVector<int>> getHillKey(QString key) {
    QVector<QVector<int>> m(2, QVector<int>(2));
    if (key.length() < 4) key = "GYBN"; // default
    key = key.toUpper();
    m[0][0] = key[0].unicode() - 'A';
    m[0][1] = key[1].unicode() - 'A';
    m[1][0] = key[2].unicode() - 'A';
    m[1][1] = key[3].unicode() - 'A';
    return m;
}

QString hillEncrypt(QString text, QString key) {
    text = text.toUpper().remove(' ');
    if (text.length() % 2 != 0) text += 'X';

    auto M = getHillKey(key);
    QString result;

    for (int i = 0; i < text.length(); i += 2) {
        int a = text[i].unicode() - 'A';
        int b = text[i + 1].unicode() - 'A';

        int x = (M[0][0] * a + M[0][1] * b) % 26;
        int y = (M[1][0] * a + M[1][1] * b) % 26;

        result += QChar(x + 'A');
        result += QChar(y + 'A');
    }

    return result;
}

QString hillDecrypt(QString text, QString key) {
    text = text.toUpper().remove(' ');

    auto M = getHillKey(key);
    int det = (M[0][0]*M[1][1] - M[0][1]*M[1][0]) % 26;
    if (det < 0) det += 26;

    int invDet = -1;
    for (int i = 0; i < 26; i++)
        if ((det * i) % 26 == 1)
            invDet = i;

    QVector<QVector<int>> inv(2, QVector<int>(2));
    inv[0][0] =  ( M[1][1] * invDet) % 26;
    inv[0][1] = (-M[0][1] * invDet + 26) % 26;
    inv[1][0] = (-M[1][0] * invDet + 26) % 26;
    inv[1][1] =  ( M[0][0] * invDet) % 26;

    QString result;

    for (int i = 0; i < text.length(); i += 2) {
        int a = text[i].unicode() - 'A';
        int b = text[i + 1].unicode() - 'A';

        int x = (inv[0][0] * a + inv[0][1] * b) % 26;
        int y = (inv[1][0] * a + inv[1][1] * b) % 26;

        result += QChar(x + 'A');
        result += QChar(y + 'A');
    }

    return result;
}
