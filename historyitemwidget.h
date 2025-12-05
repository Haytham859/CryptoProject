#ifndef HISTORYITEMWIDGET_H
#define HISTORYITEMWIDGET_H

#include <QFrame>
#include <QString>

class HistoryItemWidget : public QFrame {
    Q_OBJECT
public:
    explicit HistoryItemWidget(const QString &type, const QString &algo, const QString &original, const QString &result, QWidget *parent = nullptr);
};

#endif // HISTORYITEMWIDGET_H
