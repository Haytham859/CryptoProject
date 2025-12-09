#ifndef ANALYSISDIALOG_H
#define ANALYSISDIALOG_H

#include <QDialog>
#include <QMap>
#include <QString>

class QVBoxLayout;

class AnalysisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnalysisDialog(const QString &text, QWidget *parent = nullptr);

private:
    void analyzeText(const QString &text);
    double calculateIoC(const QMap<QChar, int> &counts, int totalLetters);
    QVBoxLayout *mainLayout;
};

#endif // ANALYSISDIALOG_H
