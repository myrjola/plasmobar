#include "plasmobar.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>

#include <plasma/svg.h>
#include <plasma/theme.h>

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

void Plasmobar::init()
{
    // A small demonstration of the setFailedToLaunch function
}


void Plasmobar::paintInterface(QPainter *p,
        const QStyleOptionGraphicsItem *option, const QRect &contentsRect)
{
    p->setRenderHint(QPainter::SmoothPixmapTransform);
    p->setRenderHint(QPainter::Antialiasing);

    // Now we draw the applet, starting with our svg
    m_svg.resize((int)contentsRect.width(), (int)contentsRect.height());
    m_svg.paint(p, (int)contentsRect.left(), (int)contentsRect.top());

    p->setPen(Qt::white);
    p->drawText(contentsRect,
                Qt::AlignLeft,
                "Hello Plasmoid!");
    p->restore();
}

// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(plasmobar, Plasmobar)

#include "plasmobar.moc"
