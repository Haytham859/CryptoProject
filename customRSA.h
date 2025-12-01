#ifndef CUSTOMRSA_H 
#define CUSTOMRSA_H

#include <QString>
#include <tuple>

QString rsaEncryptCustom(const QString &text, const QString &keyP_str, const QString &keyQ_str);
QString rsaDecryptCustom(const QString &text, const QString &keyP_str, const QString &keyQ_str);

#endif
