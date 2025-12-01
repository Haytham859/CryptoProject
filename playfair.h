#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <QString>

QString playfairEncrypt(QString text, QString key);
QString playfairDecrypt(QString text, QString key);

QString generatePlayfairTable(QString key);
QString prepareText(QString text);

#endif
