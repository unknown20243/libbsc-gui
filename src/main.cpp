#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    app.setPalette(darkPalette);

    QWidget window;
    window.setWindowTitle("libbsc GUI");

    auto *layout = new QVBoxLayout(&window);

    QLabel *fileLabel = new QLabel("Select file to compress:");
    QPushButton *browseButton = new QPushButton("Browse...");
    QLineEdit *filePath = new QLineEdit();

    QObject::connect(browseButton, &QPushButton::clicked, [&]() {
        QString file = QFileDialog::getOpenFileName(nullptr, "Select file");
        if (!file.isEmpty()) filePath->setText(file);
    });

    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(filePath);
    fileLayout->addWidget(browseButton);

    QPushButton *compressBtn = new QPushButton("Compress to BSC");
    QObject::connect(compressBtn, &QPushButton::clicked, [&]() {
        QString input = filePath->text();
        if (input.isEmpty()) {
            QMessageBox::warning(nullptr, "Error", "Please select a file first!");
            return;
        }
        QString output = input + ".bsc";
        QProcess process;
        process.start("bsc.exe", QStringList() << "e" << input << output);
        process.waitForFinished(-1);
        QMessageBox::information(nullptr, "Done", "Compression completed!");
    });

    layout->addWidget(fileLabel);
    layout->addLayout(fileLayout);
    layout->addWidget(compressBtn);

    window.setLayout(layout);
    window.resize(500, 200);
    window.show();

    return app.exec();
}
