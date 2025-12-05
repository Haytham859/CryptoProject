#include "historydialog.h"
#include "historyitemwidget.h"
#include <QVBoxLayout>
#include <QPushButton>

HistoryDialog::HistoryDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("🔒 Encryption History");
    setFixedSize(450, 500);
    setStyleSheet("background-color: #1c1c1c; font-family: 'Segoe UI';");

    QVBoxLayout *layout = new QVBoxLayout(this);

    historyList = new QListWidget(this);
    historyList->setStyleSheet(
        "QListWidget {"
        "   background-color: #2e2e2e;"
        "   border: 1px solid #17a2b8;"
        "   border-radius: 12px;"
        "   padding: 5px;"
        "}"
        "QListWidget::item {"
        "   margin: 3px;"
        "}"
        );
    layout->addWidget(historyList);

    QPushButton *clearBtn = new QPushButton("Clear History");
    clearBtn->setStyleSheet(
        "QPushButton { background-color: #17a2b8; color: white; border-radius: 10px; padding: 8px; }"
        "QPushButton:hover { background-color: #138496; }"
        );
    layout->addWidget(clearBtn);

    connect(clearBtn, &QPushButton::clicked, [=](){
        historyList->clear();
    });
}

// ---- أضف عنصر جديد كـ بطاقة ----
void HistoryDialog::addEntry(const QString &type, const QString &algo, const QString &original, const QString &result) {
    QListWidgetItem *item = new QListWidgetItem(historyList);
    HistoryItemWidget *widget = new HistoryItemWidget(type, algo, original, result);
    item->setSizeHint(widget->sizeHint());
    historyList->addItem(item);
    historyList->setItemWidget(item, widget);
    historyList->scrollToBottom();
}

