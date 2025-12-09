#ifndef RSA_H
#define RSA_H

#include <QString>
#include <tuple>
#include <QRandomGenerator>

std::tuple<int,int,int> generateRSAKeys();
QString rsaEncrypt(const QString &text, const QString &n_e, const QString &d_e);
QString rsaDecrypt(const QString &text, const QString &n_d, const QString &e_d);

#endif
