#ifndef CRYPTODESK_H
#define CRYPTODESK_H

#include "historydialog.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

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
    void importHtmlReport();
    void handleLabReport();
    void performExport();
    void performImport();

private:
    QLineEdit *inputText;
    QLineEdit *keyInput;
    QLineEdit *keyInput2;
    QPlainTextEdit *outputText;
    QComboBox *algoCombo;
    QLabel *algoInfo;
    QLabel *labelKey2;
    QPushButton *generateDesKeyBtn;
    QString generateDESKey();


    QPushButton *importBtn;

    HistoryDialog *historyDialog;
};

#endif // CRYPTODESK_H
