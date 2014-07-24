set(fiforeader_engine_SRCS
    fiforeaderengine.cpp
)

add_library(plasma_dataengine_fiforeader MODULE ${fiforeader_engine_SRCS})
target_link_libraries(plasma_dataengine_fiforeader
    KF5::Plasma
    KF5::Service
)

kservice_desktop_to_json(plasma_dataengine_fiforeader plasma-dataengine-fiforeader.desktop)

install(TARGETS plasma_dataengine_fiforeader DESTINATION ${PLUGIN_INSTALL_DIR}/plasma/dataengine)
install(FILES plasma-dataengine-fiforeader.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
