#include "transposition.h"
#include <algorithm>

// Rail Fence
QString railFenceEncrypt(const QString &text, int key) {
    if (key <= 1) return text;
    QStringList rails; rails.fill("", key);
    int row = 0, dir = 1;
    for (QChar c : text) {
        rails[row] += c;
        if (row == 0) dir = 1;
        else if (row == key-1) dir = -1;
        row += dir;
    }
    return rails.join("");
}

QString railFenceDecrypt(const QString &text, int key) {
    if (key <= 1) return text;
    int n = text.length();
    QVector<int> count(key,0);
    int row = 0, dir = 1;
    for (int i=0;i<n;i++) {
        count[row]++;
        if (row==0) dir=1;
        else if (row==key-1) dir=-1;
        row+=dir;
    }
    QVector<QString> rails(key);
    int idx=0;
    for(int r=0;r<key;r++){
        rails[r]=text.mid(idx,count[r]);
        idx+=count[r];
    }
    QString result;
    row=0; dir=1;
    QVector<int> pos(key,0);
    for(int i=0;i<n;i++){
        result += rails[row][pos[row]];
        pos[row]++;
        if(row==0) dir=1;
        else if(row==key-1) dir=-1;
        row+=dir;
    }
    return result;
}

// Columnar
QString columnarEncrypt(const QString &text, int key) {
    QString result;
    QString cleanText = text;
    int nCol = key;
    // int nRow = (text.length() + nCol -1)/nCol;

    QVector<QString> grid(nCol);
    for(int i=0;i<text.length();i++) grid[i%nCol] += cleanText[i];

    for(int j = 0; j < nCol; j++){
        result += grid[j];
    }

    return result;
}

QString columnarDecrypt(const QString &text, int key) {
    int nCol = key;
    int nRow = (text.length() + nCol -1)/nCol;
    QString cleanText = text;
    QString result;

    QVector<int> colLen(nCol,nRow);
    int extra = nRow*nCol - text.length();
    for(int i=nCol-extra;i<nCol;i++) colLen[i]--;

    QVector<QString> grid(nCol);
    int idx=0;
    for(int j = 0; j < nCol; j++){
        grid[j] = cleanText.mid(idx, colLen[j]);
        idx += colLen[j];
    }

    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nCol; j++){
            if(i < grid[j].length()) {
                result += grid[j][i];
            }
        }
    }

    return result;
}

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
