#ifndef PLASMOBAR_HEADER
#define PLASMOBAR_HEADER

#include <Plasma/Applet>

#include <plasma/widgets/label.h>

// Define our plasma Applet
class Plasmobar : public Plasma::Applet
{
    Q_OBJECT
public:
    // Basic Create/Destroy
    Plasmobar(QObject *parent, const QVariantList &args);
    ~Plasmobar();

	void init();

public slots:
	void updateLabel(const QString& content);

private:
    Plasma::Label* m_label;
};

#endif
