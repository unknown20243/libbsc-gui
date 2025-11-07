#pragma once
#include <QWidget>
#include <QString>

class QLineEdit;
class QPushButton;
class QComboBox;
class QTextEdit;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QLineEdit *filePath;
    QPushButton *browseButton;
    QPushButton *compressBtn;
    QPushButton *decompressBtn;
    QComboBox *blockSizeBox;
    QComboBox *algorithmBox;
    QComboBox *entropyBox;
    QTextEdit *logArea;

    void setupUI();
    void connectSignals();
    void appendLog(const QString &text);
    void runBSC(const QString &mode);
};
