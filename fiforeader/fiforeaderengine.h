#ifndef FIFOREADERENGINE_H
#define FIFOREADERENGINE_H

#include <Plasma/DataEngine>

/**
 * Reads named pipes
 */
class FIFOReaderEngine : public Plasma::DataEngine
{
    // required since Plasma::DataEngine inherits QObject
    Q_OBJECT

    public:
        // every engine needs a constructor with these arguments
        FIFOReaderEngine(QObject* parent, const QVariantList& args);

    protected:
        // this virtual function is called when a new source is requested
        bool sourceRequestEvent(const QString& name);

        // this virtual function is called when an automatic update
        // is triggered for an existing source (ie: when a valid update
        // interval is set when requesting a source)
        bool updateSourceEvent(const QString& source);

    protected Q_SLOTS:
        void newLine(const QString &line);
};

#endif // FIFOREADERENGINE_H
