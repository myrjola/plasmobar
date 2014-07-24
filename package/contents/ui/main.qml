import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as Components
import org.kde.plasma.plasmoid 2.0

Item {
    id: plasmobar
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
        text: "XMonad"
        textFormat: Text.RichText
    }
}
