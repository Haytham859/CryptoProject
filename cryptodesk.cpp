#include "cryptodesk.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QGraphicsDropShadowEffect>

// Include all cipher headers
#include "caesar.h"
#include "playfair.h"
#include "hill.h"
#include "multiplicative.h"
#include "affine.h"
#include "dna.h"
#include "vigenere.h"
#include "autokey.h"
#include "vernam.h"
#include "transposition.h"
#include "rsa.h"

#include <QRandomGenerator>

// Helper function for RSA key generation
#include <tuple>

CryptoDesk::CryptoDesk(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("🔐 CryptoDesk – Modular Encryption");
    resize(700, 650);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QLabel *labelText = new QLabel("Enter Text:");
    inputText = new QLineEdit();

    QLabel *labelKey = new QLabel("Key a:");
    keyInput = new QLineEdit();

    QLabel *labelKey2 = new QLabel("Key b (Affine only):");
    keyInput2 = new QLineEdit();
    keyInput2->setPlaceholderText("Second key b for Affine");
    keyInput2->setVisible(false);

    QLabel *labelAlgo = new QLabel("Algorithm:");
    algoCombo = new QComboBox();
    algoCombo->addItem("Caesar Cipher");
    algoCombo->addItem("Playfair Cipher");
    algoCombo->addItem("Hill Cipher (2x2)");
    algoCombo->addItem("Multiplicative Cipher");
    algoCombo->addItem("Affine Cipher");
    algoCombo->addItem("DNA Cipher");
    algoCombo->addItem("Vigenère Cipher");
    algoCombo->addItem("Autokey Cipher");
    algoCombo->addItem("Vernam Cipher");
    algoCombo->addItem("Rail Fence Cipher");
    algoCombo->addItem("Columnar Cipher");
    algoCombo->addItem("Row Transposition Cipher");
    algoCombo->addItem("RSA Cipher");

    algoInfo = new QLabel("Select an algorithm to see info.");

    QPushButton *encryptBtn = new QPushButton("Encrypt");
    QPushButton *decryptBtn = new QPushButton("Decrypt");
    QPushButton *fileBtn = new QPushButton("Encrypt File");
    QPushButton *generateKeyBtn = new QPushButton("Generate RSA Key");

    QLineEdit *publicKeyOutput = new QLineEdit();
    QLineEdit *privateKeyOutput = new QLineEdit();
    publicKeyOutput->setReadOnly(true);
    privateKeyOutput->setReadOnly(true);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(encryptBtn);
    btnLayout->addWidget(decryptBtn);
    btnLayout->addWidget(fileBtn);
    btnLayout->addWidget(generateKeyBtn);

    outputText = new QPlainTextEdit();
    outputText->setReadOnly(true);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(labelText);
    layout->addWidget(inputText);
    layout->addWidget(labelKey);
    layout->addWidget(keyInput);
    layout->addWidget(labelKey2);
    layout->addWidget(keyInput2);
    layout->addWidget(labelAlgo);
    layout->addWidget(algoCombo);
    layout->addWidget(algoInfo);
    layout->addLayout(btnLayout);
    layout->addWidget(new QLabel("Public Key (n, e):"));
    layout->addWidget(publicKeyOutput);
    layout->addWidget(new QLabel("Private Key (n, d):"));
    layout->addWidget(privateKeyOutput);
    layout->addWidget(outputText);

    addShadow(encryptBtn);
    addShadow(decryptBtn);
    addShadow(fileBtn);
    addShadow(generateKeyBtn);

    connect(encryptBtn, &QPushButton::clicked, this, &CryptoDesk::encryptText);
    connect(decryptBtn, &QPushButton::clicked, this, &CryptoDesk::decryptText);
    connect(fileBtn, &QPushButton::clicked, this, &CryptoDesk::encryptFile);
    connect(algoCombo, &QComboBox::currentTextChanged, this, &CryptoDesk::updateAlgoInfo);

    connect(generateKeyBtn, &QPushButton::clicked, [=](){
        auto [n,e,d] = generateRSAKeys();
        publicKeyOutput->setText(QString("(%1, %2)").arg(n).arg(e));
        privateKeyOutput->setText(QString("(%1, %2)").arg(n).arg(d));
    });

    updateAlgoInfo();
}

void CryptoDesk::updateAlgoInfo() {
    QString algo = algoCombo->currentText();
    keyInput2->setVisible(false);
    if (algo == "Caesar Cipher") algoInfo->setText("Caesar Cipher: shift letters by a numeric key.");
    else if (algo == "Playfair Cipher") algoInfo->setText("Playfair Cipher: uses digraphs and a keyword matrix.");
    else if (algo == "Hill Cipher (2x2)") algoInfo->setText("Hill Cipher 2x2: uses 2x2 matrix multiplication.");
    else if (algo=="Multiplicative Cipher") algoInfo->setText("Multiplicative Cipher: multiply letters by key modulo 26 (key must be coprime with 26).");
    else if (algo=="Affine Cipher") { algoInfo->setText("Affine Cipher: E(x) = (a*x + b) mod 26, 'a' coprime with 26"); keyInput2->setVisible(true);}
    else if (algo == "DNA Cipher") algoInfo->setText("DNA Cipher: encodes text using nucleotide mapping.");
    else if (algo == "Vigenère Cipher") algoInfo->setText("Vigenère Cipher: polyalphabetic cipher using a keyword.");
    else if (algo == "Autokey Cipher") algoInfo->setText("Autokey Cipher: extends the key with plaintext.");
    else if (algo == "Vernam Cipher") algoInfo->setText("Vernam Cipher: XOR with a one-time pad key.");
    else if (algo == "Rail Fence Cipher") algoInfo->setText("Rail Fence Cipher: transposition using zigzag pattern.");
    else if (algo == "Columnar Cipher") algoInfo->setText("Columnar Cipher: text arranged in columns based on key.");
    else if (algo == "Row Transposition Cipher") algoInfo->setText("Row Transposition Cipher: permutes rows according to key.");
    else if (algo == "RSA Cipher") algoInfo->setText("RSA Cipher: asymmetric encryption using public/private keys.");
}

void CryptoDesk::encryptText() {
    QString text = inputText->text();
    if (text.isEmpty()) { QMessageBox::warning(this,"Warning","Please enter text!"); return; }

    QString algo = algoCombo->currentText();
    QString result;

    if (algo == "Caesar Cipher") result = caesarEncrypt(text, keyInput->text().toInt());
    else if (algo == "Playfair Cipher") result = playfairEncrypt(text, keyInput->text());
    else if (algo == "Multiplicative Cipher") result = multiplicativeEncrypt(text, keyInput->text().toInt());
    else if (algo == "Hill Cipher (2x2)") result = hillEncrypt(text, keyInput->text());
    else if (algo == "Affine Cipher") { int a = keyInput->text().toInt(); int b = keyInput2->text().toInt(); result = affineEncrypt(text,a,b);}
    else if (algo == "DNA Cipher") result = dnaEncrypt(text);
    else if (algo == "Vigenère Cipher") result = vigenereEncrypt(text,keyInput->text());
    else if (algo == "Autokey Cipher") result = autokeyEncrypt(text,keyInput->text());
    else if (algo == "Vernam Cipher") result = vernamEncrypt(text,keyInput->text());
    else if (algo == "Rail Fence Cipher") result = railFenceEncrypt(text,keyInput->text().toInt());
    else if (algo == "Columnar Cipher") result = columnarEncrypt(text,keyInput->text());
    else if (algo == "Row Transposition Cipher") result = rowTranspositionEncrypt(text,keyInput->text());
    else if (algo == "RSA Cipher") result = rsaEncrypt(text,keyInput->text(), keyInput2->text());

    outputText->setPlainText(result);
}

void CryptoDesk::decryptText() {
    QString text = inputText->text();
    if (text.isEmpty()) { QMessageBox::warning(this,"Warning","Please enter text!"); return; }

    QString algo = algoCombo->currentText();
    QString result;

    if (algo == "Caesar Cipher") result = caesarDecrypt(text, keyInput->text().toInt());
    else if (algo == "Playfair Cipher") result = playfairDecrypt(text, keyInput->text());
    else if (algo == "Multiplicative Cipher") result = multiplicativeDecrypt(text, keyInput->text().toInt());
    else if (algo == "Hill Cipher (2x2)") result = hillDecrypt(text, keyInput->text());
    else if (algo == "Affine Cipher") { int a = keyInput->text().toInt(); int b = keyInput2->text().toInt(); result = affineDecrypt(text,a,b);}
    else if (algo == "DNA Cipher") result = dnaDecrypt(text);
    else if (algo == "Vigenère Cipher") result = vigenereDecrypt(text,keyInput->text());
    else if (algo == "Autokey Cipher") result = autokeyDecrypt(text,keyInput->text());
    else if (algo == "Vernam Cipher") result = vernamDecrypt(text,keyInput->text());
    else if (algo == "Rail Fence Cipher") result = railFenceDecrypt(text,keyInput->text().toInt());
    else if (algo == "Columnar Cipher") result = columnarDecrypt(text,keyInput->text());
    else if (algo == "Row Transposition Cipher") result = rowTranspositionDecrypt(text,keyInput->text());
    else if (algo == "RSA Cipher") result = rsaDecrypt(text,keyInput->text(), keyInput2->text());

    outputText->setPlainText(result);
}

void CryptoDesk::encryptFile() {
    QString fileName = QFileDialog::getOpenFileName(this,"Select file");
    if(fileName.isEmpty()) return;

    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&f);
    QString content = in.readAll();
    f.close();

    QString algo = algoCombo->currentText();
    QString result;

    if (algo == "Caesar Cipher") result = caesarEncrypt(content,keyInput->text().toInt());
    else if (algo == "Playfair Cipher") result = playfairEncrypt(content,keyInput->text());
    else if (algo == "Multiplicative Cipher") result = multiplicativeEncrypt(content,keyInput->text().toInt());
    else if (algo == "Hill Cipher (2x2)") result = hillEncrypt(content,keyInput->text());
    else if (algo == "Affine Cipher") { int a = keyInput->text().toInt(); int b = keyInput2->text().toInt(); result = affineEncrypt(content,a,b);}
    else if (algo == "DNA Cipher") result = dnaEncrypt(content);
    else if (algo == "Vigenère Cipher") result = vigenereEncrypt(content,keyInput->text());
    else if (algo == "Autokey Cipher") result = autokeyEncrypt(content,keyInput->text());
    else if (algo == "Vernam Cipher") result = vernamEncrypt(content,keyInput->text());
    else if (algo == "Rail Fence Cipher") result = railFenceEncrypt(content,keyInput->text().toInt());
    else if (algo == "Columnar Cipher") result = columnarEncrypt(content,keyInput->text());
    else if (algo == "Row Transposition Cipher") result = rowTranspositionEncrypt(content,keyInput->text());
    else if (algo == "RSA Cipher") result = rsaEncrypt(content,keyInput->text(), keyInput2->text());

    QString save = QFileDialog::getSaveFileName(this,"Save encrypted file");
    if(save.isEmpty()) return;

    QFile out(save);
    out.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream s(&out);
    s << result;
    out.close();

    QMessageBox::information(this,"Done","File encrypted successfully!");
}

void CryptoDesk::addShadow(QWidget *widget) {
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(15);
    shadow->setOffset(3,3);
    shadow->setColor(QColor(0,0,0,160));
    widget->setGraphicsEffect(shadow);
}
