#include "playfair.h"
#include <QVector>
#include <QString>
#include <utility>

QString generatePlayfairTable(QString key) {
    key = key.toUpper().replace("J", "I").remove(' ');
    QString table = "";
    QVector<bool> used(26, false);

    for (QChar c : key) {
        if (c.isLetter() && !used[c.unicode() - 'A']) {
            used[c.unicode() - 'A'] = true;
            table += c;
        }
    }

    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            table += c;
            used[c - 'A'] = true;
        }
    }
    return table;
}

QString prepareText(QString text) {
    text = text.toUpper().replace("J", "I").remove(' ');
    QString prepared = "";

    int i = 0;
    while (i < text.length()) {
        QChar a = text[i];

        if (i + 1 < text.length()) {
            QChar b = text[i + 1];

            if (a == b) {
                prepared += a;
                prepared += 'X';
                i += 1;
            } else {
                prepared += a;
                prepared += b;
                i += 2;
            }
        } else {
            prepared += a;
            prepared += 'X';
            i += 1;
        }
    }
    return prepared;
}


QString playfairEncrypt(QString text, QString key) {
    QString table = generatePlayfairTable(key);
    QString preparedText = prepareText(text);
    QString result = "";

    for (int i = 0; i < preparedText.length(); i += 2) {
        QChar a = preparedText[i];
        QChar b = preparedText[i + 1];

        int idx1 = table.indexOf(a);
        int idx2 = table.indexOf(b);

        int r1 = idx1 / 5, c1 = idx1 % 5;
        int r2 = idx2 / 5, c2 = idx2 % 5;

        if (r1 == r2) {
            c1 = (c1 + 1) % 5;
            c2 = (c2 + 1) % 5;
        } else if (c1 == c2) {
            r1 = (r1 + 1) % 5;
            r2 = (r2 + 1) % 5;
        } else {
            std::swap(c1, c2);
        }

        result += table[r1 * 5 + c1];
        result += table[r2 * 5 + c2];
    }
    return result;
}

QString playfairDecrypt(QString text, QString key) {
    text = text.toUpper().remove(' ');
    QString table = generatePlayfairTable(key);
    QString result = "";

    for (int i = 0; i < text.length(); i += 2) {
        QChar a = text[i];
        QChar b = (i + 1 < text.length()) ? text[i + 1] : 'X';

        int idx1 = table.indexOf(a);
        int idx2 = table.indexOf(b);

        int r1 = idx1 / 5, c1 = idx1 % 5;
        int r2 = idx2 / 5, c2 = idx2 % 5;

        if (r1 == r2) {
            c1 = (c1 + 4) % 5;
            c2 = (c2 + 4) % 5;
        } else if (c1 == c2) {
            r1 = (r1 + 4) % 5;
            r2 = (r2 + 4) % 5;
        } else {
            std::swap(c1, c2);
        }

        result += table[r1 * 5 + c1];
        result += table[r2 * 5 + c2];
    }
    return result;
}


// QString generatePlayfairTable(QString key) {
//     key = key.toUpper().remove('J');
//     QString table;
//     QVector<bool> used(26, false);

//     for (QChar c : key) {
//         if (c.isLetter() && !used[c.unicode() - 'A']) {
//             used[c.unicode() - 'A'] = true;
//             table += c;
//         }
//     }

//     for (char c = 'A'; c <= 'Z'; ++c) {
//         if (c == 'J') continue;
//         if (!used[c - 'A']) table += c;
//     }

//     return table;
// }

// QPair<QChar, QChar> adjustPair(QChar a, QChar b) {
//     if (a == b) b = 'X';
//     return { a, b };
// }

// QString playfairEncrypt(QString text, QString key) {
//     text = text.toUpper().remove(' ').replace("J", "I");
//     QString table = generatePlayfairTable(key);

//     QString result;
//     for (int i = 0; i < text.length(); i += 2) {
//         QChar a = text[i];
//         QChar b = (i + 1 < text.length()) ? text[i + 1] : 'X';

//         auto p = adjustPair(a, b);
//         a = p.first; b = p.second;

//         int idx1 = table.indexOf(a);
//         int idx2 = table.indexOf(b);

//         int r1 = idx1 / 5, c1 = idx1 % 5;
//         int r2 = idx2 / 5, c2 = idx2 % 5;

//         if (r1 == r2) { c1 = (c1 + 1) % 5; c2 = (c2 + 1) % 5; }
//         else if (c1 == c2) { r1 = (r1 + 1) % 5; r2 = (r2 + 1) % 5; }
//         else std::swap(c1, c2);

//         result += table[r1 * 5 + c1];
//         result += table[r2 * 5 + c2];
//     }

//     return result;
// }

// QString playfairDecrypt(QString text, QString key) {
//     text = text.toUpper().remove(' ');
//     QString table = generatePlayfairTable(key);

//     QString result;
//     for (int i = 0; i < text.length(); i += 2) {
//         QChar a = text[i];
//         QChar b = text[i + 1];

//         int idx1 = table.indexOf(a);
//         int idx2 = table.indexOf(b);

//         int r1 = idx1 / 5, c1 = idx1 % 5;
//         int r2 = idx2 / 5, c2 = idx2 % 5;

//         if (r1 == r2) { c1 = (c1 + 4) % 5; c2 = (c2 + 4) % 5; }
//         else if (c1 == c2) { r1 = (r1 + 4) % 5; r2 = (r2 + 4) % 5; }
//         else std::swap(c1, c2);

//         result += table[r1 * 5 + c1];
//         result += table[r2 * 5 + c2];
//     }
//     return result;
// }
