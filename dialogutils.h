#ifndef DIALOGUTILS_H
#define DIALOGUTILS_H

#include <QString>
#include <QWidget>

class DialogUtils
{
public:
    static void showAlgorithmHelp(QWidget *parent, const QString &algoName);

    static void showAbout(QWidget *parent);
};

#endif // DIALOGUTILS_H
