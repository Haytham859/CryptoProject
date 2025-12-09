#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QListWidget>

class HistoryDialog : public QDialog {
    Q_OBJECT
public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    void addEntry(const QString &type, const QString &algo, const QString &original, const QString &result);

private:
    QListWidget *historyList;
};

#endif // HISTORYDIALOG_H
