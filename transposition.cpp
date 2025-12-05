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

// Row Transposition (مثال بسيط)
QString rowTranspositionEncrypt(const QString &text, const QString &key) {
    QString cleanText = text;
    int nCol = key.length();
    int padding = (nCol - (cleanText.length() % nCol)) % nCol;
    for(int i = 0; i < padding; i++) {
        cleanText += 'X';
    }

    QVector<QString> grid(nCol);
    for(int i=0;i<cleanText.length();i++) grid[i%nCol] += cleanText[i];

    QString tempKey = key;
    QString sortedKey = tempKey;
    std::sort(sortedKey.begin(), sortedKey.end());

    QString result;
    for(QChar c : sortedKey){
        int idx = tempKey.indexOf(c);
        result += grid[idx];
        tempKey[idx] = '*';
    }
    return result;
}

QString rowTranspositionDecrypt(const QString &text, const QString &key) {
    int nCol = key.length();
    int nRow = text.length() / nCol;

    QVector<QString> grid(nCol);
    int idx=0;

    QString tempKey = key;
    QString sortedKey = tempKey;
    std::sort(sortedKey.begin(), sortedKey.end());

    for(QChar c : sortedKey){
        int k = tempKey.indexOf(c);
        grid[k] = text.mid(idx, nRow);
        idx += nRow;
        tempKey[k]='*';
    }

    QString result;
    for(int i = 0; i < nRow; i++){
        for(int j = 0; j < nCol; j++){
            result += grid[j][i];
        }
    }
    return result;
}
