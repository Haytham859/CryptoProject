#include "cryptodesk.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QGraphicsDropShadowEffect>
#include <QRegularExpression>
#include <QInputDialog>
#include <QSettings>

// Include all cipher headers
#include "historydialog.h"
#include "htmlexporter.h"
#include "dna.h"
#include "vigenere.h"
#include "vernam.h"
#include "transposition.h"
#include "Des.h"
#include "AES.h"
#include "dialogutils.h"
#include "analysisdialog.h"

#include <QRandomGenerator>


CryptoDesk::CryptoDesk(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("🔐 CryptoDesk – Modular Encryption");
    resize(700, 650);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);


    // ----- Dark/Light Styles -----
    QString darkStyle = R"(
        QWidget { background-color: #1e1e1e; color: #f0f0f0; font-family: Segoe UI, Helvetica, Arial; font-size: 11pt; }
        QLineEdit, QPlainTextEdit, QComboBox { background-color: #2d2d30; color: #ffffff; border: 1px solid #3c3c3c; border-radius: 5px; padding: 5px; }
        QPushButton { background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #138496, stop:1 #138496); color: #ffffff; border-radius: 6px; padding: 8px 15px; }
        QPushButton:hover { background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #17a2b8, stop:1 #17a2b8); }
    )";

    QString lightStyle = R"(
        QWidget { background-color: #f0f0f0; color: #000000; font-family: Segoe UI, Helvetica, Arial; font-size: 11pt; }
        QLineEdit, QPlainTextEdit, QComboBox { background-color: #ffffff; color: #000000; border: 1px solid #ccc; border-radius: 5px; padding: 5px; }
        QPushButton { background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #000000, stop:1 #000000); color: #ffffff; border-radius: 6px; padding: 8px 15px; }
        QPushButton:hover { background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d0d0d0, stop:1 #b0b0b0);
                            color: #000000;
                        }
    )";

    // ----- Header -----
    QLabel *appTitle = new QLabel("Crypto Desktop");
    appTitle->setStyleSheet("font-size: 22px; font-weight: bold; color: white; margin-left: 40px;");
    appTitle->setAlignment(Qt::AlignCenter);
    
    QPushButton *aboutBtn = new QPushButton("About");
    aboutBtn->setCursor(Qt::PointingHandCursor);
    aboutBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   color: #17a2b8;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "   border-radius: 15px;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "color: white;"
        "   background-color: #138496;"
        "}"
        );
    QPushButton *historyBtn = new QPushButton("History");
    historyBtn->setCursor(Qt::PointingHandCursor);
    historyBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   color: #17a2b8;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "   border-radius: 15px;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   color: white;"
        "   background-color: #138496;"
        "}"
        );
    connect(historyBtn, &QPushButton::clicked, [=](){
        historyDialog->show();
    });



        // ----- Dark/Light Theme Button -----
    QPushButton *themeBtn = new QPushButton("🌙");
    themeBtn->setCursor(Qt::PointingHandCursor);
    themeBtn->setStyleSheet(
        "QPushButton { background-color: transparent; color: #17a2b8; font-weight: bold; font-size: 14px; border-radius: 15px; border: none; }"
        "QPushButton:hover { color: white; background-color: #138496; }"
        );

    bool isDark = true;
    this->setStyleSheet(darkStyle); // تم التعديل لتطبيق الثيم على النافذة بدلاً من qApp

    connect(themeBtn, &QPushButton::clicked, [=, &isDark]() mutable {
        if(isDark) {
            this->setStyleSheet(lightStyle);
            themeBtn->setText("☀️");
            appTitle->setStyleSheet("font-size: 22px; font-weight: bold; color: black; margin-left: 40px;");
            isDark = false;
        } else {
            this->setStyleSheet(darkStyle);
            themeBtn->setText("🌙");
            appTitle->setStyleSheet("font-size: 22px; font-weight: bold; color: white; margin-left: 40px;");
            isDark = true;
        }
        QSettings settings("MyCompany", "CryptoDesk"); // حفظ الثيم باستخدام QSettings
        settings.setValue("isDarkTheme", isDark);
    });
    
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addStretch();
    headerLayout->addStretch();
    headerLayout->addWidget(appTitle);
    headerLayout->addStretch();
    headerLayout->addWidget(aboutBtn);
    headerLayout->addWidget(historyBtn);
    headerLayout->addWidget(themeBtn, 0, Qt::AlignRight);


    // ----- Input Fields -----
    QLabel *labelText = new QLabel("Enter Text:");
    inputText = new QLineEdit();
    inputText->setStyleSheet("padding: 5px;");

    QLabel *labelKey = new QLabel("Key a:");
    keyInput = new QLineEdit();
    keyInput->setStyleSheet("padding: 5px;");

    labelKey2 = new QLabel("Key b:");
    keyInput2 = new QLineEdit();
    labelKey2->setVisible(false);
    keyInput2->setVisible(false);

    // ----- Algorithm ComboBox -----
    QLabel *labelAlgo = new QLabel("Algorithm:");
    algoCombo = new QComboBox();
    algoCombo->addItems({
        "DNA Cipher",
        "Vigenère Cipher",
        "Vernam Cipher",
        "Row Transposition Cipher",
        "DES Cipher",
        "AES Cipher"
    });
    algoCombo->setStyleSheet("margin-bottom: 5px;");

    algoInfo = new QLabel("Select an algorithm to see info.");

    QPushButton *helpBtn = new QPushButton("?");
    helpBtn->setFixedSize(30, 30);
    helpBtn->setCursor(Qt::PointingHandCursor);
    helpBtn->setToolTip("Algorithm Guide");
    helpBtn->setStyleSheet(
        "QPushButton { background-color: transparent; color: #138496; font-weight: bold; font-size: 18px; border-radius: 15px; border: 1px solid white; padding: 0px; }"
        "QPushButton:hover { background-color: white; }"
        );

    QHBoxLayout *algoLayout = new QHBoxLayout();
    algoLayout->addWidget(algoCombo);
    algoLayout->addWidget(helpBtn);


    // ----- Buttons -----
    QPushButton *encryptBtn = new QPushButton("Encrypt");
    QPushButton *decryptBtn = new QPushButton("Decrypt");
    QPushButton *fileBtn = new QPushButton("Encrypt File");
    encryptBtn->setCursor(Qt::PointingHandCursor);
    decryptBtn->setCursor(Qt::PointingHandCursor);
    fileBtn->setCursor(Qt::PointingHandCursor);

    QPushButton *analyzeBtn = new QPushButton("Analyze");
    addShadow(analyzeBtn);
    analyzeBtn->setCursor(Qt::PointingHandCursor);

    importBtn = new QPushButton("Lab Report System");
    addShadow(importBtn);
    importBtn->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(encryptBtn);
    btnLayout->addWidget(decryptBtn);
    btnLayout->addWidget(fileBtn);
    btnLayout->addWidget(analyzeBtn);
    btnLayout->addWidget(importBtn);

    generateDesKeyBtn = new QPushButton("Generate DES Key");
    generateDesKeyBtn->setCursor(Qt::PointingHandCursor);
    generateDesKeyBtn->setVisible(false); // مخفي أول مرة
    addShadow(generateDesKeyBtn);
    btnLayout->addWidget(generateDesKeyBtn); // اضفها مرة واحدة فقط

    // ضيف الزر لمكان مناسب في Layout
    // الربط مع الدالة
    connect(generateDesKeyBtn, &QPushButton::clicked, [=]() {
        QString desKey = generateDESKey();  // مهم: استدعاء الدالة بالاقواس ()
        keyInput->setText(desKey);
    });

    outputText = new QPlainTextEdit();
    outputText->setReadOnly(true);
    outputText->setStyleSheet("margin-top: 5px;");

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addLayout(headerLayout);
    layout->addWidget(labelText);
    layout->addWidget(inputText);
    layout->addWidget(labelKey);
    layout->addWidget(keyInput);
    layout->addWidget(labelAlgo);
    layout->addLayout(algoLayout);
    layout->addLayout(btnLayout);

    QPushButton *clearBtn = new QPushButton("Clear All");
    btnLayout->addWidget(clearBtn);

    layout->addWidget(outputText);

    addShadow(encryptBtn);
    addShadow(decryptBtn);
    addShadow(fileBtn);
    addShadow(clearBtn);

    // ----- Initialize HistoryDialog -----
    historyDialog = new HistoryDialog(this);

    // ----- Connections -----
    connect(encryptBtn, &QPushButton::clicked, this, &CryptoDesk::encryptText);
    connect(decryptBtn, &QPushButton::clicked, this, &CryptoDesk::decryptText);
    connect(fileBtn, &QPushButton::clicked, this, &CryptoDesk::encryptFile);
    connect(algoCombo, &QComboBox::currentTextChanged, this, &CryptoDesk::updateAlgoInfo);

    connect(helpBtn, &QPushButton::clicked, [=](){
        DialogUtils::showAlgorithmHelp(this, algoCombo->currentText());
    });

    connect(aboutBtn, &QPushButton::clicked, [=](){
        DialogUtils::showAbout(this);
    });

    connect(clearBtn, &QPushButton::clicked, [=](){
        inputText->clear();
        keyInput->clear();
        outputText->clear();
        inputText->setFocus();
    });

    connect(analyzeBtn, &QPushButton::clicked, [=](){
        QString textToAnalyze = outputText->toPlainText();
        if (textToAnalyze.isEmpty()) {
            textToAnalyze = inputText->text();
        }
        if (textToAnalyze.isEmpty()) {
            QMessageBox::warning(this, "Empty", "No text to analyze!");
            return;
        }
        AnalysisDialog dlg(textToAnalyze, this);
        dlg.exec();
    });

    connect(importBtn, &QPushButton::clicked, this, &CryptoDesk::handleLabReport);

    updateAlgoInfo();
}

QString CryptoDesk::generateDESKey() {
    QString key;
    const QString chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (int i = 0; i < 8; ++i) {  // مفتاح DES طوله 8 بايت
        int index = QRandomGenerator::global()->bounded(chars.length());
        key.append(chars[index]);
    }
    return key;
}

void CryptoDesk::updateAlgoInfo() {
    QString algo = algoCombo->currentText();
    // ---------- Default: Hide optional widgets ----------
    importBtn->setVisible(false);
    generateDesKeyBtn->setVisible(false);


    // ---------- Update placeholders and info ----------
    if (algo == "DNA Cipher"){
        importBtn->setVisible(true);
        algoInfo->setText("DNA Cipher: encodes text using nucleotide mapping.");
        inputText->setPlaceholderText("Enter a text ( e.g.: Hello World! ) ");
        keyInput->setPlaceholderText("Enter a text as a key ( e.g.: My Secret Key ) ");
    }
    else if (algo == "Vigenère Cipher"){
        algoInfo->setText("Vigenère Cipher: polyalphabetic cipher using a keyword.");
        inputText->setPlaceholderText("Enter a text ( e.g.: Lemon ) ");
        keyInput->setPlaceholderText("Enter Text as a key ( e.g.: Pizza ) ");
    }
    else if (algo == "Vernam Cipher"){
        algoInfo->setText("Vernam Cipher: XOR with a one-time pad key.");
        inputText->setPlaceholderText("Enter a text ( e.g.: HELLO ) ");
        keyInput->setPlaceholderText("Enter Text as a key ( e.g.: SON ) ");
    }
    else if (algo == "Row Transposition Cipher"){
        algoInfo->setText("Row Transposition Cipher: permutes rows according to key.");
        inputText->setPlaceholderText("Enter a text ( e.g.: attack postponed until two am ) ");
        keyInput->setPlaceholderText("Enter numbers according to the desired array order ( e.g.: 412367 ) ");
    }
    else if (algo == "DES Cipher") {
        algoInfo->setText("DES Cipher: symmetric 64-bit block cipher.");
        inputText->setPlaceholderText("Enter text (e.g.: Hello World)");
        keyInput->setPlaceholderText("Enter a key (e.g.: MySecretKey)");
        generateDesKeyBtn->setVisible(true);
    }

}

bool CryptoDesk::validateInputs() {
    QString algo = algoCombo->currentText();
    QString key1 = keyInput->text().trimmed();
    QString key2 = keyInput2->text().trimmed();

    if (key1.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Key cannot be empty!");
        return false;
    }
    if (key1.contains(" ")) {
        QMessageBox::warning(this, "Input Error", "Remove Spaces!");
        return false;
    }

    QRegularExpression isNumber("^[0-9]+$");
    QRegularExpression isText("^[a-zA-Z]+$");
    QRegularExpression isHex("^[0-9A-Fa-f]+$");  // <-- اضف ده
    if (algo == "AES Cipher") {
        // فقط تحقق من إن المفتاح والنص مش فاضي
        if (key1.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Key cannot be empty!");
            return false;
        }
        if (inputText->text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Text cannot be empty!");
            return false;
        }
    }


    // =========================================================
    // المجموعة الثانية: خوارزميات تحتاج حروف فقط (String Keys)
    // =========================================================
    else if (algo == "Vigenère Cipher" || algo == "Vernam Cipher" || algo == "DNA Cipher") {
        if (!isText.match(key1).hasMatch()) {
            QMessageBox::warning(this, "Input Error", QString("The key for %1 must contain English letters only (No numbers or symbols)!").arg(algo));
            return false;
        }
    }

    else if (algo == "Row Transposition Cipher") {

        if (!isNumber.match(key1).hasMatch()) {
            QMessageBox::warning(this, "Input Error", "Row Transposition key usually consists of numbers (e.g., 4312)!");
            return false;
        }
    }

    return true;
}


void CryptoDesk::encryptText() {
    QString text = inputText->text();
    QString algo = algoCombo->currentText();
    QString result;

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter text!");
        return;
    }

    if (!validateInputs()) return;

    // ----- تشفير حسب الخوارزمية -----
    if (algo == "DNA Cipher") result = dnaEncrypt(text, keyInput->text());
    else if (algo == "Vigenère Cipher") result = vigenereEncrypt(text, keyInput->text());
    else if (algo == "Vernam Cipher") result = vernamEncrypt(text, keyInput->text());
    else if (algo == "Row Transposition Cipher") result = rowTranspositionEncrypt(text, keyInput->text());
    else if (algo == "DES Cipher") {
        result= desEncryptText(text,keyInput->text()) ;
    }
    else if (algo == "AES Cipher") {
        result=aesEncryptText(text,keyInput->text()) ;
    }
    // ----- عرض الناتج -----
    outputText->setPlainText(result);

    // ----- سجل العملية في History -----
    if (!result.isEmpty()) {
        QString shortInput = text;
        QString shortResult = result;

        // اختصار النصوص الطويلة لأناقة العرض
        if (shortInput.length() > 200) shortInput = shortInput.left(200) + "...";
        if (shortResult.length() > 200) shortResult = shortResult.left(200) + "...";

        historyDialog->addEntry("Encrypted", algo, shortInput, shortResult);
    }
}

void CryptoDesk::decryptText() {
    QString text = inputText->text();
    QString algo = algoCombo->currentText();
    QString result;

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter text!");
        return;
    }

    if (!validateInputs()) return;

    if (algo == "DNA Cipher") result = dnaDecrypt(text, keyInput->text());
    else if (algo == "Vigenère Cipher") result = vigenereDecrypt(text, keyInput->text());
    else if (algo == "Vernam Cipher") result = vernamDecrypt(text, keyInput->text());
    else if (algo == "Row Transposition Cipher") result = rowTranspositionDecrypt(text, keyInput->text());
    else if (algo == "DES Cipher") {
        result=desDecryptText(text,keyInput->text()) ;
    }
    else if (algo == "AES Cipher") {
        result=aesDecryptText(text,keyInput->text()) ;
    }
    // ----- عرض الناتج -----
    outputText->setPlainText(result);

    // ----- سجل العملية في History -----
    if (!result.isEmpty()) {
        QString shortInput = text;
        QString shortResult = result;

        // اختصار النصوص الطويلة لأناقة العرض
        if (shortInput.length() > 200) shortInput = shortInput.left(200) + "...";
        if (shortResult.length() > 200) shortResult = shortResult.left(200) + "...";

        historyDialog->addEntry("Decrypted", algo, shortInput, shortResult);
    }
}

void CryptoDesk::encryptFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Select file");
    if (fileName.isEmpty()) return;

    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&f);
    QString content = in.readAll();
    f.close();    

    QString algo = algoCombo->currentText();
    QString result;

    if (!validateInputs()) return;

    // ----- تشفير حسب الخوارزمية -----
    if (algo == "DNA Cipher") result = dnaEncrypt(content, keyInput->text());
    else if (algo == "Vigenère Cipher") result = vigenereEncrypt(content, keyInput->text());
    else if (algo == "Vernam Cipher") result = vernamEncrypt(content, keyInput->text());
    else if (algo == "Row Transposition Cipher") result = rowTranspositionEncrypt(content, keyInput->text());


    QString save = QFileDialog::getSaveFileName(this, "Save encrypted file");
    if (save.isEmpty()) return;

    QFile out(save);
    if (!out.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Cannot create output file!");
        return;
    }
    QTextStream s(&out);
    s << result;
    out.close();

    QMessageBox::information(this, "Done", "File encrypted successfully!");

    // ----- سجل العملية في History -----
    QString fileShortName = QFileInfo(fileName).fileName();
    historyDialog->addEntry("Encrypted", algo, fileShortName, "Output saved to: " + QFileInfo(save).fileName());
}

void CryptoDesk::addShadow(QWidget *widget) {
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setBlurRadius(15);
    shadow->setOffset(3,3);
    shadow->setColor(QColor(0,0,0,160));
    widget->setGraphicsEffect(shadow);
}

void CryptoDesk::handleLabReport() {
    // Prompt user for action
    QMessageBox msgBox;
    msgBox.setWindowTitle("Lab Report System");
    msgBox.setText("Please select an action:");
    msgBox.setIcon(QMessageBox::Question);

    // Add custom buttons
    QAbstractButton *pExportBtn = msgBox.addButton("📝 Generate New Report", QMessageBox::YesRole);
    QAbstractButton *pImportBtn = msgBox.addButton("📂 Open Existing Report", QMessageBox::NoRole);
    msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();

    // Handle user selection
    if (msgBox.clickedButton() == pExportBtn) {
        // Validate inputs
        if (inputText->text().isEmpty()) {
            QMessageBox::warning(this, "Missing Data", "Cannot generate report: Diagnosis result (Text) is empty!");
            return;
        }
        if (keyInput->text().isEmpty()) {
            QMessageBox::warning(this, "Missing Data", "Cannot generate report: Sample ID (Key) is empty!");
            return;
        }

        // Proceed to export
        performExport();

    } else if (msgBox.clickedButton() == pImportBtn) {
        // Proceed to import
        performImport();
    }
}

void CryptoDesk::performExport() {
    // Get input data
    QString diagnosis = inputText->text();
    QString sampleID = keyInput->text();

    // Optional: Ask for patient name
    bool ok;
    QString patientName = QInputDialog::getText(this, "Patient Data", "Enter Patient Name:", QLineEdit::Normal, "John Doe", &ok);
    if (!ok) return;

    // Encrypt data
    QString encryptedDNA = dnaEncrypt(diagnosis, sampleID);

    // Open save dialog
    QString fileName = QFileDialog::getSaveFileName(this, "Save Report", "Report.html", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;

    // Generate and save HTML
    if (HtmlExporter::saveLabReport(fileName, patientName, sampleID, encryptedDNA)) {
        QMessageBox::information(this, "Success", "Report Generated!");
    }
}

void CryptoDesk::performImport() {
    // Open file dialog
    QString fileName = QFileDialog::getOpenFileName(this, "Select Report", "", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;

    // Parse report file
    ReportData data = HtmlExporter::parseLabReport(fileName);

    if (data.isValid) {
        // Decrypt data
        QString result = dnaDecrypt(data.encryptedData, data.sampleID);

        // Update UI
        algoCombo->setCurrentText("DNA Cipher");
        inputText->setText(data.encryptedData);
        keyInput->setText(data.sampleID);
        outputText->setPlainText("Report Loaded:\n" + result);

        QMessageBox::information(this, "Done", "Report Decoded Successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Invalid Report File!");
    }
}

void CryptoDesk::importHtmlReport() {
    // Open file dialog
    QString fileName = QFileDialog::getOpenFileName(this, "Select Lab Report", "", "HTML Files (*.html)");
    if (fileName.isEmpty()) return;

    // Parse data
    ReportData data = HtmlExporter::parseLabReport(fileName);

    // Validate and display
    if (data.isValid) {
       // Decrypt data
        inputText->setText(data.encryptedData);
        QString decryptedDiagnosis = dnaDecrypt(data.encryptedData, data.sampleID);

        // Update UI
        algoCombo->setCurrentText("DNA Cipher");
        keyInput->setText(data.sampleID);
        outputText->setPlainText("Decrypted from HTML Report:\n" + decryptedDiagnosis);

        QMessageBox::information(this, "Success", "Report loaded and decrypted successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Invalid Report Format!\nCould not find Sample ID or DNA Data.");
    }
}
