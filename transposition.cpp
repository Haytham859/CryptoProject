#include "transposition.h"
#include <algorithm>

QString rowTranspositionEncrypt(const QString &text, const QString &key) {
    if (key.isEmpty()) return ""; // حماية من القسمة على صفر

    int nCol = key.length();
    int nRow = (text.length() + nCol - 1) / nCol;

    // إضافة padding لو النص مش مكمل الأعمدة
    QString cleanText = text;
    int padding = nRow * nCol - text.length();
    for (int i = 0; i < padding; i++) cleanText += 'X';

    // إنشاء الجدول صفوف x أعمدة
    QVector<QString> grid(nRow);
    for (int i = 0; i < nRow; i++) {
        grid[i] = cleanText.mid(i * nCol, nCol);
    }

    // ترتيب الأعمدة حسب المفتاح
    QString result;
    QString sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());

    QString tempKey = key;
    for (QChar c : sortedKey) {
        int colIndex = tempKey.indexOf(c);
        for (int row = 0; row < nRow; row++) {
            result += grid[row][colIndex];
        }
        tempKey.replace(colIndex, 1, "*");
    }

    return result;
}

QString rowTranspositionDecrypt(const QString &text, const QString &key) {
    if (key.isEmpty()) return ""; // حماية من القسمة على صفر
    int nCol = key.length();

    // التحقق من أن طول النص يقبل القسمة على طول المفتاح (سلامة البيانات)
    if (text.length() % nCol != 0) return "Error: Corrupted Text";

    int nRow = text.length() / nCol;

    // إنشاء الأعمدة الفارغة
    QVector<QString> columns(nCol);

    QString sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());

    QString tempKey = key;

    int idx = 0;
    for (QChar c : sortedKey) {
        int colIndex = tempKey.indexOf(c);
        columns[colIndex] = text.mid(idx, nRow);
        idx += nRow;
        tempKey.replace(colIndex, 1, "*");
    }

    // إعادة قراءة النص بالصفوف
    QString result;
    for (int row = 0; row < nRow; row++) {
        for (int col = 0; col < nCol; col++) {
            result += columns[col][row];
        }
    }

    // --- (الإضافة الجديدة) إزالة الحشو 'X' من النهاية ---
    // نقوم بحذف X من النهاية طالما وجدت، ولكن نحذر من حذف X أصلية إذا كانت جزءاً من الكلمة
    // في التشفير البسيط عادة نفترض أن آخر حروف X هي حشو.
    while (result.endsWith('X')) {
        result.chop(1);
    }

    return result;
}
