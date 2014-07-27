import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as Components
import org.kde.plasma.plasmoid 2.0

Item {
    id: main


    Layout.minimumWidth: vertical ? 0 : sizehelper.paintedWidth + (units.smallSpacing * 2)
    Layout.maximumWidth: vertical ? Infinity : Layout.minimumWidth
    Layout.preferredWidth: vertical ? undefined : Layout.minimumWidth

    Layout.minimumHeight: vertical ? sizehelper.paintedHeight + (units.smallSpacing * 2) : 0
    Layout.maximumHeight: vertical ? Layout.minimumHeight : Infinity
    Layout.preferredHeight: vertical ? Layout.minimumHeight : theme.mSize(theme.defaultFont).height * 2

    property int formFactor: plasmoid.formFactor
    property int timePixelSize: theme.defaultFont.pixelSize
    property int timezonePixelSize: theme.smallestFont.pixelSize

    property bool constrained: formFactor == PlasmaCore.Types.Vertical || formFactor == PlasmaCore.Types.Horizontal

    property bool vertical: plasmoid.formFactor == PlasmaCore.Types.Vertical

    PlasmaCore.DataSource {
            id: dataSource
            engine: "fiforeader"
            connectedSources: ["XMonad"]
            onNewData:{
                    if(sourceName== "XMonad"){
                            label.text = data.XMonad
                    }
            }

    }

    // We don't want an icon when in panel.
    Plasmoid.compactRepresentation: Plasmoid.fullRepresentation

    Components.Label  {
        id: label
        textFormat: Text.StyledText
        font {
            pixelSize: 1024
            pointSize: 0 // we need to unset pointSize otherwise it breaks the Text.Fit size mode
        }
        minimumPixelSize: theme.mSize(theme.smallestFont).height
        fontSizeMode: Text.Fit
        wrapMode: Text.NoWrap
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        height: 0
        width: 0
        anchors {
            fill: parent
            margins: units.smallSpacing
        }
    }

    // I don't know why this invisible sizehelper is needed, but it works for the digital-clock Plasmoid as well.
    Text {
        id: sizehelper
        font.pixelSize: vertical ? theme.mSize(theme.defaultFont).height * 2 : 1024 // random "big enough" size - this is used as a max pixelSize by the fontSizeMode
        minimumPixelSize: theme.mSize(theme.smallestFont).height
        verticalAlignment: Text.AlignVCenter

        fontSizeMode: Text.Fit

        wrapMode: Text.NoWrap
        visible: false
        anchors {
            fill: parent
            margins: units.smallSpacing
        }
    }
}
