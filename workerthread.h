#ifndef PLASMOBAR_HEADER
#define PLASMOBAR_HEADER
#include <QThread>
#include <plasma/widgets/label.h>

class WorkerThread : public QThread
{
private:
    Plasma::Label* m_label;

public:
    WorkerThread(QObject * parent, Plasma::Label* label);

    Q_OBJECT
    void run();

signals:
    void resultReady();
};

#endif
