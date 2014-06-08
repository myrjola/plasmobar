import QtQuick 1.0
import org.kde.plasma.core 0.1 as PlasmaCore

Item {
        PlasmaCore.DataSource {
                id: dataSource
                engine: "fiforeader"
                connectedSources: ["XMonad"]
                interval: 500
 
                onNewData:{
                        local.text = data.XMonad
                }
        }
        Text{
            id: local
            color: "light grey"
        }
}
