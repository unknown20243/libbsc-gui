#include "gui.h"
#include "bsc_runner.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setupUI();
    connectSignals();
}

void MainWindow::setupUI() {
    setWindowTitle("libbsc GUI");
    resize(600, 400);

    auto *layout = new QVBoxLayout(this);

    auto *fileLabel = new QLabel("Select file:");
    filePath = new QLineEdit();
    browseButton = new QPushButton("Browse");

    auto *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(filePath);
    fileLayout->addWidget(browseButton);

    // Options
    auto *optionsLayout = new QHBoxLayout();

    blockSizeBox = new QComboBox();
    for (int i : {1, 5, 10, 25, 50, 100, 200, 512, 1024, 2047})
        blockSizeBox->addItem(QString("-b%1").arg(i));

    algorithmBox = new QComboBox();
    algorithmBox->addItems({"-m0", "-m3", "-m4", "-m5", "-m6", "-m7", "-m8"});

    entropyBox = new QComboBox();
    entropyBox->addItems({"-e0", "-e1", "-e2"});

    optionsLayout->addWidget(new QLabel("Block Size:"));
    optionsLayout->addWidget(blockSizeBox);
    optionsLayout->addWidget(new QLabel("Algorithm:"));
    optionsLayout->addWidget(algorithmBox);
    optionsLayout->addWidget(new QLabel("Entropy:"));
    optionsLayout->addWidget(entropyBox);

    compressBtn = new QPushButton("Compress");
    decompressBtn = new QPushButton("Decompress");

    logArea = new QTextEdit();
    logArea->setReadOnly(true);

    layout->addWidget(fileLabel);
    layout->addLayout(fileLayout);
    layout->addLayout(optionsLayout);
    layout->addWidget(compressBtn);
    layout->addWidget(decompressBtn);
    layout->addWidget(new QLabel("Log:"));
    layout->addWidget(logArea);
}

void MainWindow::connectSignals() {
    connect(browseButton, &QPushButton::clicked, [this]() {
        QString file = QFileDialog::getOpenFileName(this, "Select file");
        if (!file.isEmpty())
            filePath->setText(file);
    });

    connect(compressBtn, &QPushButton::clicked, [this]() {
        runBSC("e");
    });

    connect(decompressBtn, &QPushButton::clicked, [this]() {
        runBSC("d");
    });
}

void MainWindow::appendLog(const QString &text) {
    logArea->append(text);
}

void MainWindow::runBSC(const QString &mode) {
    QString input = filePath->text();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a file first!");
        return;
    }

    QString output = (mode == "e") ? input + ".bsc" : input + ".out";

    QStringList args;
    args << mode << input << output
         << blockSizeBox->currentText()
         << algorithmBox->currentText()
         << entropyBox->currentText();

    appendLog("Running: bsc " + args.join(' '));

    QString result = runBSCProcess(args);
    appendLog(result);
}
