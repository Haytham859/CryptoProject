#ifndef CRYPTODESK_H
#define CRYPTODESK_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLabel>
#include <qpushbutton.h>

class CryptoDesk : public QMainWindow
{
    Q_OBJECT

public:
    CryptoDesk(QWidget *parent = nullptr);

private slots:
    void encryptText();
    void decryptText();
    void encryptFile();
    void updateAlgoInfo();
    void addShadow(QWidget *widget);
    bool validateInputs();

private:
    QLineEdit *inputText;
    QLineEdit *keyInput;
    QLineEdit *keyInput2;
    QPlainTextEdit *outputText;
    QComboBox *algoCombo;
    QLabel *algoInfo;
    QLabel *labelKey2;
    QPushButton *generateKeyBtn;

    QLabel *labelPub;
    QLineEdit *publicKeyOutput;

    QLabel *labelPriv;
    QLineEdit *privateKeyOutput;
};

#endif // CRYPTODESK_H
