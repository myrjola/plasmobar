#include "plasmobar.h"
#include <QCoreApplication>
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <QGraphicsLinearLayout>
#include <QTimer>
#include <QThread>
#include <QDebug>


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
    : Plasma::Applet(parent, args)
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
        qDebug()<<"Worker::mainLoop get called from?: "<<QThread::currentThreadId();
        int m_pipe_fd = open("/tmp/xmonadfifo", O_RDONLY | O_NONBLOCK);
        int ret;
        fd_set fdset;
        char buff[1000];
        int len = 1000;
        if (m_pipe_fd != -1) {
            while (true) {
                FD_ZERO(&fdset);
                FD_SET(m_pipe_fd,&fdset);
                struct timeval tv;
                tv.tv_sec = 1;
                tv.tv_usec = 0;
                ret = select(m_pipe_fd+1,&fdset,NULL,NULL,&tv);
                if (ret > 0) {
                    read(m_pipe_fd, buff, len);
                    emit requestLabelUpdate(QString(buff));
                }
                else if ( ret == 0 ) {
                }
                else {
                    qDebug() << "Error returned from select: " << ret << endl;
                    break;
                }
            }
        }
        qDebug() << "FIFOReader thread exiting..." << ret << endl;
        ::close(m_pipe_fd);
    }
signals:
    void requestLabelUpdate(const QString &);
};

void Plasmobar::init()
{
   QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(this);

  m_label = new Plasma::Label(this);
  m_label->setWordWrap(false);

  layout->addItem(m_label);

  FIFOReader *worker = new FIFOReader();
  QThread* thread = new QThread();
  QTimer* timer = new QTimer();
  timer->start(1000);
  timer->setSingleShot(true);
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
