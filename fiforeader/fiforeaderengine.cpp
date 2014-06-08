#include "fiforeaderengine.h"

#include <QString>

#include <Plasma/DataContainer>

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
    QString xmonadLog = "<fc=#429942>[1-term]</fc> 2-emacs 3-www 4-dev 5-music 7 8 9-chat : Tall : <fc=orange>KF5 : zsh – Konsole</fc>";
    setData(name, I18N_NOOP("XMonad"), xmonadLog);
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
