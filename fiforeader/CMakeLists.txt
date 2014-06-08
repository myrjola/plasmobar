# A name for the project
project(plasma-fiforeader)

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

# We add our source code here
set(fiforeader_engine_SRCS fiforeaderengine.cpp)

# Now make sure all files get to the right place
kde4_add_plugin(plasma_engine_fiforeader ${fiforeader_engine_SRCS})
target_link_libraries(plasma_engine_fiforeader
                      ${KDE4_KDECORE_LIBS}
                      ${KDE4_PLASMA_LIBS})

install(TARGETS plasma_engine_fiforeader
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-engine-fiforeader.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
