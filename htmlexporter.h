#ifndef HTMLEXPORTER_H
#define HTMLEXPORTER_H

#include <QString>

struct ReportData {
    QString sampleID;
    QString encryptedData;
    bool isValid;
};

class HtmlExporter
{
public:
    static bool saveLabReport(QString filePath, QString patientName, QString sampleID, QString encryptedDna);

    static ReportData parseLabReport(QString filePath);
};

#endif // HTMLEXPORTER_H
