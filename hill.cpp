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

int modInverseHill(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int mathMod(int a, int b) {
    return (a % b + b) % b;
}

QString hillEncrypt(QString text, QString key) {
    if (key.length() < 4){
        QMessageBox::warning(nullptr,"ERROR","Key must be 4 characters");
        return " ";
    }
    text = text.toUpper().remove(' ');
    if (text.length() % 2 != 0) text += 'X';

    auto M = getHillKey(key);
    QString result;

    for (int i = 0; i < text.length(); i += 2) {
        int a = text[i].unicode() - 'A';
        int b = text[i + 1].unicode() - 'A';

        int c1 = mathMod(M[0][0] * a + M[0][1] * b, 26);
        int c2 = mathMod(M[1][0] * a + M[1][1] * b, 26);

        result += QChar(c1 + 'A');
        result += QChar(c2 + 'A');
    }

    return result;
}

QString hillDecrypt(QString text, QString key) {
    if (key.length() < 4){
        QMessageBox::warning(nullptr,"ERROR","Key must be 4 characters");
        return " ";
    }

    text = text.toUpper().remove(' ');
    if (text.length() % 2 != 0) text += 'X';

    auto M = getHillKey(key);
    int det = (M[0][0]*M[1][1] - M[0][1]*M[1][0]);
    det = mathMod(det, 26);
    int detInv = modInverseHill(det, 26);

    if (detInv == -1) {
        QMessageBox::warning(nullptr,"ERROR","Key is not invertible (Determinant has no inverse).");
        return " ";
    }

    QVector<QVector<int>> K_inv(2, QVector<int>(2));
    K_inv[0][0] = mathMod(detInv * M[1][1], 26);
    K_inv[0][1] = mathMod(detInv * -M[0][1], 26);
    K_inv[1][0] = mathMod(detInv * -M[1][0], 26);
    K_inv[1][1] = mathMod(detInv * M[0][0], 26);

    QString result;

    for (int i = 0; i < text.length(); i += 2) {
        int a = text[i].unicode() - 'A';
        int b = text[i + 1].unicode() - 'A';

        int p1 = mathMod(K_inv[0][0] * a + K_inv[0][1] * b, 26);
        int p2 = mathMod(K_inv[1][0] * a + K_inv[1][1] * b, 26);

        result += QChar(p1 + 'A');
        result += QChar(p2 + 'A');
    }

    return result;
}
