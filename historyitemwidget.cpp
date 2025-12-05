#include "historyitemwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>

HistoryItemWidget::HistoryItemWidget(const QString &type, const QString &algo, const QString &original, const QString &result, QWidget *parent)
    : QFrame(parent)
{
    setStyleSheet(
        "QFrame {"
        "   background-color: #2b2b2b;"
        "   border-radius: 10px;"
        "   padding: 8px;"
        "}"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10,5,10,5);

    // العنوان: النوع + الخوارزمية + الوقت
    QLabel *title = new QLabel(QString("[%1] %2 - %3")
                                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                   .arg(type)
                                   .arg(algo));
    title->setStyleSheet("color: #17a2b8; font-weight: bold;");
    mainLayout->addWidget(title);

    // النص الأصلي
    QLabel *origLabel = new QLabel(QString("Original: %1").arg(original));
    origLabel->setStyleSheet("color: white;");
    mainLayout->addWidget(origLabel);

    // النص الناتج
    QLabel *resultLabel = new QLabel(QString("Result: %1").arg(result));
    resultLabel->setStyleSheet("color: #00ff99;"); // لون مميز للناتج
    mainLayout->addWidget(resultLabel);
}
