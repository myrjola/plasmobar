import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as Components
import org.kde.plasma.plasmoid 2.0

Item {
    id: main

    height: 50
    width: 200

    Layout.fillWidth: true

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
    Plasmoid.preferredRepresentation: Plasmoid.fullRepresentation

    Components.Label  {
        id: label
        clip: true
        anchors.fill: parent
        textFormat: Text.StyledText
        fontSizeMode: Text.VerticalFit
        font.pointSize: 72
    }
}
