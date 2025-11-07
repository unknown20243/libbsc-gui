#include "bsc_runner.h"
#include <QProcess>

QString runBSCProcess(const QStringList &args) {
    QProcess process;
    process.start("bsc.exe", args);
    process.waitForFinished(-1);

    QString output = process.readAllStandardOutput();
    QString error = process.readAllStandardError();

    return output + "\n" + error;
}
