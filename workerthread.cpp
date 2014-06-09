#include "workerthread.h"

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


WorkerThread::WorkerThread(QObject * parent, Plasma::Label* label) :
    QThread(parent),
    m_label(label) {};


void WorkerThread::run() {
    int ret;
    fd_set fdset;
    char buff[1000];
    int len = 1000;

    int pipe_fd = open("/tmp/xmonadfifo", O_RDONLY | O_NONBLOCK);
    if (pipe_fd != -1) {
        while (true) {
            FD_ZERO(&fdset);
            FD_SET(pipe_fd,&fdset);
            struct timeval tv;
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            ret = select(pipe_fd+1,&fdset,NULL,NULL,&tv);
            if (ret > 0) {
                read(pipe_fd, buff, len);
                m_label->setText(QString(buff));
            }
            else if ( ret == 0 ) {
                // Timeout
                continue;
            }
            else {
                break;
            }
        }
    }
    ::close(pipe_fd);

    emit resultReady();
}

#include "plasmobar.moc"
