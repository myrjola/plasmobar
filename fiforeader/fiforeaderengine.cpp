#include "fiforeaderengine.h"

#include <QString>
#include <QCoreApplication>
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QByteArray>
#include <QTextCodec>
#include <QStringBuilder>

#include <Plasma/DataContainer>

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <climits>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>

using namespace std;

class FIFOReader : public QObject
{
    Q_OBJECT
public slots:
    void mainLoop()
    {
        qDebug() << "FIFOReader::mainLoop starting";
        FILE *fp;
        int c;
        QByteArray buffer;
        QString line;
        qDebug() << "FIFOReader::mainLoop opening file";
        string filename("/tmp/xmonadfifo");
        fp = fopen(filename.c_str(), "r");
        if (fp != NULL) {
            while((c=getc(fp)) != EOF)
            {
                char ch = (char) c;
                buffer.append(ch);
                if ((ch) == '\n') {
                    line = QTextCodec::codecForMib(106)->toUnicode(buffer);
                    emit requestLabelUpdate(line);
                    buffer.clear();
                }
            }
            fclose(fp);
        }
        line = QString("Could not open file: ") % QString(filename.c_str());
        emit requestLabelUpdate(line);
        qDebug() << "FIFOReader::mainLoop thread exiting...";
    }

signals:
    void requestLabelUpdate(const QString &);
};

FIFOReaderEngine::FIFOReaderEngine(QObject* parent, const QVariantList& args)
    : Plasma::DataEngine(parent, args)
{
    // We ignore any arguments - data engines do not have much use for them
    Q_UNUSED(args)

    // This prevents applets from setting an unnecessarily high
    // update interval and using too much CPU.
    // In the case of a clock that only has second precision,
    // a third of a second should be more than enough.
    setMinimumPollingInterval(333);

    FIFOReader *worker = new FIFOReader();
    QThread* thread = new QThread();
    // TODO: figure out how to start this thread without using a QTimer
    QTimer* timer = new QTimer();
    timer->start(1000);
    //timer->setSingleShot(true);
    worker->moveToThread(thread);
    timer->moveToThread(thread);
    connect(timer, SIGNAL(timeout()), worker, SLOT(mainLoop()));
    connect(worker, SIGNAL(requestLabelUpdate(QString)), this, SLOT(newLine(QString)));
    connect(thread, SIGNAL(destroyed()), worker, SLOT(deleteLater()));
    thread->start();
}

void FIFOReaderEngine::newLine(const QString &line)
{
    return setData("XMonad", "XMonad", line);
}

bool FIFOReaderEngine::sourceRequestEvent(const QString &name)
{
    // We do not have any special code to execute the
    // first time a source is requested, so we just call
    // updateSourceEvent().
    return updateSourceEvent(name);
}

bool FIFOReaderEngine::updateSourceEvent(const QString &name)
{
    setData(name, "XMonad", QString("XMonad"));
    return true;
}

// This does the magic that allows Plasma to load
// this plugin.
K_EXPORT_PLASMA_DATAENGINE_WITH_JSON(fiforeader, FIFOReaderEngine, "plasma-dataengine-fiforeader.json")

#include "fiforeaderengine.moc"
