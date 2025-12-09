#include "cryptodesk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Dark Mode + Fluent Style
    QString darkStyle = R"(
        QWidget {
            background-color: #1e1e1e;
            color: #f0f0f0;
            font-family: Segoe UI, Helvetica, Arial;
            font-size: 11pt;
        }
        QLineEdit, QPlainTextEdit, QComboBox {
            background-color: #2d2d30;
            color: #ffffff;
            border: 1px solid #3c3c3c;
            border-radius: 5px;
            padding: 5px;
        }
        QPushButton {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #0078d7, stop:1 #005a9e);
            color: #ffffff;
            border-radius: 6px;
            padding: 8px 15px;
        }
        QPushButton:hover {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #0096f6, stop:1 #0078d7);
        }
        QPushButton:pressed {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                              stop:0 #005a9e, stop:1 #003f6f);
        }
        QComboBox::drop-down {
            border: none;
        }
        QLabel {
            font-weight: bold;
        }
        QScrollBar:vertical {
            background: #2d2d30;
            width: 12px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background: #0078d7;
            min-height: 20px;
            border-radius: 6px;
        }
        QScrollBar::add-line, QScrollBar::sub-line {
            background: none;
        }
    )";

    a.setStyleSheet(darkStyle);

    CryptoDesk w;
    w.show();

    return a.exec();
}
