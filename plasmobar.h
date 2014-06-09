#ifndef PLASMOBAR_HEADER
#define PLASMOBAR_HEADER

#include <Plasma/Applet>

// Define our plasma Applet
class Plasmobar : public Plasma::Applet
{
    Q_OBJECT
    public:
        // Basic Create/Destroy
        Plasmobar(QObject *parent, const QVariantList &args);
        ~Plasmobar();

        // The paintInterface procedure paints the applet to screen
        void paintInterface(QPainter *p,
                const QStyleOptionGraphicsItem *option,
                const QRect& contentsRect);
	void init();
};

#endif
