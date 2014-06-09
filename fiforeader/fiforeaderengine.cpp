#include "fiforeaderengine.h"

#include <QString>

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
    int m_pipe_fd, ret;
    fd_set fdset;
    char buff[1000];
    int len = 1000;

    m_pipe_fd = open("/tmp/xmonadfifo", O_RDONLY | O_NONBLOCK);

    if (m_pipe_fd != -1) {
        FD_ZERO(&fdset);
        FD_SET(m_pipe_fd,&fdset);
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        ret = select(m_pipe_fd+1,&fdset,NULL,NULL,&tv);
        if (ret > 0) {
            read(m_pipe_fd, buff, len);
        }
        else if ( ret == 0 ) {
            break;
        }
        else {
            cout << "Error returned from select: " << ret << endl;
            break;
        }
        ::close(m_pipe_fd);
    } else {
        exit(1);
    }
    setData(name, I18N_NOOP("XMonad"), QString(buff));

    return true;
}

// This does the magic that allows Plasma to load
// this plugin.  The first argument must match
// the X-Plasma-EngineName in the .desktop file.
// The second argument is the name of the class in
// your plugin that derives from Plasma::DataEngine
K_EXPORT_PLASMA_DATAENGINE(fiforeader, FIFOReaderEngine)

// this is needed since TestTimeEngine is a QObject
#include "fiforeaderengine.moc"
