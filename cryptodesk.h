#ifndef CRYPTODESK_H
#define CRYPTODESK_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLabel>

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

private:
    QLineEdit *inputText;
    QLineEdit *keyInput;
    QLineEdit *keyInput2;
    QPlainTextEdit *outputText;
    QComboBox *algoCombo;
    QLabel *algoInfo;
};

#endif // CRYPTODESK_H
