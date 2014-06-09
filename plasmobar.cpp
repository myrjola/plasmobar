#include "plasmobar.h"

#include <QCoreApplication>
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QStringBuilder>


#include <plasma/svg.h>
#include <plasma/theme.h>

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

Plasmobar::Plasmobar(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_label(new Plasma::Label(this))
{
    resize(500, 30);
}


Plasmobar::~Plasmobar()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}

class FIFOReader : public QObject
{
    Q_OBJECT
public slots:
    void mainLoop()
    {
        qDebug() << "FIFOReader::mainLoop starting";
        FILE *fp;
        int c;
        QString line = "";
        qDebug() << "FIFOReader::mainLoop opening file";
        fp=fopen("/tmp/xmonadfifo", "r");
        if (fp != NULL) {
            while((c=getc(fp)) != EOF)
            {
                line = line % QChar((char) c);
                if (((char) c) == '\n') {
                    emit requestLabelUpdate(line);
                    line = "";
                }
            }
        }
        fclose(fp);
        qDebug() << "FIFOReader::mainLoop thread exiting...";
    }
signals:
    void requestLabelUpdate(const QString &);
};

void Plasmobar::init()
{
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);

    m_label->setWordWrap(false);

    layout->addItem(m_label);

    FIFOReader *worker = new FIFOReader();
    QThread* thread = new QThread();
    // TODO: figure out how to start this thread without using a QTimer
    QTimer* timer = new QTimer();
    timer->start(1000);
    //timer->setSingleShot(true);
    worker->moveToThread(thread);
    timer->moveToThread(thread);
    connect(timer, SIGNAL(timeout()), worker, SLOT(mainLoop()));
    connect(worker, SIGNAL(requestLabelUpdate(QString)), this, SLOT(updateLabel(QString)));
    connect(thread, SIGNAL(destroyed()), worker, SLOT(deleteLater()));
    thread->start();
}

void Plasmobar::updateLabel(const QString& content)
{
    m_label->setText(content);
}

// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(plasmobar, Plasmobar)

#include "plasmobar.moc"
