#include "dna.h"

QString dnaEncrypt(const QString &text){
    QString result;
    for(QChar c : text){
        switch(c.toLatin1()){
        case 'A': result += "AT"; break;
        case 'B': result += "CG"; break;
        default: result += c;
        }
    }
    return result;
}

QString dnaDecrypt(const QString &text){
    QString result;
    int i = 0;
    while(i < text.length()){
        QString pair = text.mid(i,2);
        if(pair=="AT") result += 'A';
        else if(pair=="CG") result += 'B';
        else result += text[i];
        i+=2;
    }
    return result;
}
