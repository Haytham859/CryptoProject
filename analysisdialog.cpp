#include "analysisdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QScrollArea>
#include <QGroupBox>
#include <cmath>
#include <QPushButton>

AnalysisDialog::AnalysisDialog(const QString &text, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("📊 Text Analysis Dashboard");
    resize(500, 600);

    mainLayout = new QVBoxLayout(this);

    // 1. Header Section
    QLabel *title = new QLabel("Frequency Analysis & Statistics");
    title->setStyleSheet("font-size: 16px; font-weight: bold; margin-bottom: 10px; color: #17a2b8;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    // 2. Perform Analysis
    analyzeText(text);

    // 3. Close Button
    QPushButton *closeBtn = new QPushButton("Close");
    // تجميل زرار الإغلاق
    closeBtn->setStyleSheet("background-color: #343a40; color: white; border-radius: 5px; padding: 8px;");
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeBtn);
}

void AnalysisDialog::analyzeText(const QString &text) {
    QMap<QChar, int> counts;
    int totalLetters = 0;
    bool isDNA = true; // هنفترض إنه DNA لحد ما نثبت العكس

    // 1. Count letters and detect type
    for (QChar c : text) {
        if (c.isLetter()) {
            QChar up = c.toUpper();
            counts[up]++;
            totalLetters++;

            // لو لقينا حرف غريب عن مكونات الـ DNA يبقى ده نص عادي
            if (up != 'A' && up != 'C' && up != 'G' && up != 'T') {
                isDNA = false;
            }
        }
    }

    // لو النص فاضي أو قصير جداً، مش هنعتبره DNA
    if (totalLetters < 4) isDNA = false;

    // --- Statistics Box ---
    QString boxTitle = isDNA ? "🧬 DNA Sequence Analysis" : "📝 General Text Analysis";
    QGroupBox *statsBox = new QGroupBox(boxTitle);
    QVBoxLayout *statsLayout = new QVBoxLayout();

    statsLayout->addWidget(new QLabel(QString("Total Length: %1 chars").arg(text.length())));
    statsLayout->addWidget(new QLabel(QString("Total Letters: %1").arg(totalLetters)));

    if (isDNA) {
        // --- تحليل خاص للـ DNA ---
        // الهدف: التأكد من العشوائية (كل حرف يكون قريب من 25%)
        double aP = (totalLetters > 0) ? (counts['A'] * 100.0) / totalLetters : 0;
        double cP = (totalLetters > 0) ? (counts['C'] * 100.0) / totalLetters : 0;
        double gP = (totalLetters > 0) ? (counts['G'] * 100.0) / totalLetters : 0;
        double tP = (totalLetters > 0) ? (counts['T'] * 100.0) / totalLetters : 0;

        bool isBalanced = (std::abs(aP - 25) < 10) && (std::abs(cP - 25) < 10) &&
                          (std::abs(gP - 25) < 10) && (std::abs(tP - 25) < 10);

        QString status = isBalanced ? "✅ Strong / Randomized (~25%)" : "⚠️ Biased / Weak Pattern";
        QString color = isBalanced ? "green" : "red";

        QLabel *statusLbl = new QLabel("Randomness: " + status);
        statusLbl->setStyleSheet("font-weight: bold; color: " + color);
        statsLayout->addWidget(statusLbl);
    }
    else {
        // --- تحليل النص العادي ---
        double ioc = calculateIoC(counts, totalLetters);
        QString iocType = (ioc > 0.06) ? "(Likely English)" : "(Likely Random/Encrypted)";
        statsLayout->addWidget(new QLabel(QString("Index of Coincidence (IoC): %1\n%2").arg(ioc, 0, 'f', 4).arg(iocType)));
    }

    statsBox->setLayout(statsLayout);
    mainLayout->addWidget(statsBox);

    // --- Frequency Bars (Scrollable) ---
    QScrollArea *scroll = new QScrollArea();
    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);

    // لو DNA هنعرض 4 حروف بس، لو نص عادي هنعرض الأبجدية كلها
    QString charsToShow = isDNA ? "ACGT" : "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (QChar c : charsToShow) {
        int count = counts.value(c, 0);
        double percentage = (totalLetters > 0) ? (count * 100.0 / totalLetters) : 0;

        QHBoxLayout *row = new QHBoxLayout();

        QLabel *lbl = new QLabel(QString(c));
        lbl->setFixedWidth(30);
        lbl->setStyleSheet("font-weight: bold; font-size: 14px;");

        QProgressBar *bar = new QProgressBar();
        bar->setRange(0, 100);
        bar->setValue(static_cast<int>(percentage));
        bar->setTextVisible(false);

        // --- Color Coding Logic ---
        QString color = "#007bff"; // أزرق افتراضي

        if (isDNA) {
            // في الـ DNA: الأخضر هو الحلو (قريب من 25%)، والأحمر هو الوحش (بعيد أوي)
            if (percentage > 40 || percentage < 10) color = "#dc3545"; // أحمر (توزيع سيء)
            else if (percentage > 20 && percentage < 30) color = "#28a745"; // أخضر (توزيع مثالي)
            else color = "#ffc107"; // أصفر (نص نص)
        } else {
            // في النص العادي: الأحمر يعني تكرار عالي (زي حرف E)
            if (percentage > 10.0) color = "#dc3545";
        }

        bar->setStyleSheet(QString("QProgressBar::chunk { background-color: %1; border-radius: 3px; }").arg(color));

        QLabel *perc = new QLabel(QString("%1%").arg(percentage, 0, 'f', 1));
        perc->setFixedWidth(50);
        perc->setAlignment(Qt::AlignRight);

        row->addWidget(lbl);
        row->addWidget(bar);
        row->addWidget(perc);

        scrollLayout->addLayout(row);
    }

    scrollWidget->setLayout(scrollLayout);
    scroll->setWidget(scrollWidget);
    scroll->setWidgetResizable(true);

    mainLayout->addWidget(scroll);
}

double AnalysisDialog::calculateIoC(const QMap<QChar, int> &counts, int totalLetters) {
    if (totalLetters <= 1) return 0.0;

    double sum = 0.0;
    for (int count : counts) {
        sum += count * (count - 1);
    }
    // Formula: Sum(n * n-1) / (N * N-1)
    return sum / (totalLetters * (static_cast<double>(totalLetters) - 1));
}
