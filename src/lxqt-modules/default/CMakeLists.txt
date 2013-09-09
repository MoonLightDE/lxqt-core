# _lxqt-core module build script #
#TODO: Add internationalization support

cmake_minimum_required(VERSION 2.8)



SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

# Use the name of the main module class 
set(MODULE "LxqtMod_Default")
set(lxqt-core_PATH "/usr/local")

set(MODULE_HEADERS
    LxqtMod_Default.h
)

set(MODULE_PUBLIC_INTERFACES
    LxqtMod_Default.h
)


set(MODULE_SOURCES
    LxqtMod_Default.cpp
)

set(MODULE_MOCS
    LxqtMod_Default.h
)

set(MODULE_UIS
)

set(MODULE_RESOURCES
)

# Edit the module descriptor template
configure_file( Descriptor.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}.desktop )
set(MODULE_DESCRIPTOR
    ${MODULE}.desktop
)

# Exclude main.cpp from compilation
foreach(item ${razor-runner_CPP_FILES} )
    if(NOT item MATCHES "main.cpp")
        SET ( nomain-razor-runner_CPP_FILES
            ${nomain-razor-runner_CPP_FILES}
            ${item} )
    endif(NOT item MATCHES "main.cpp")

endforeach(item)


# Include libs
set(EXTERNAL_LIBS

#   Remember to always include the Qt Libraries
#   ${QT_LIBRARIES}
)


#*******************************************#
#       Don't modify the code below         #
#*******************************************#

set(PROJECT "${MODULE}")
project(${PROJECT})



SET( LIBRARY_OUTPUT_PATH lib/lxqt-core/modules )
SET( DESCRIPTOR_OUTPUT_PATH share/lxqt-core/descriptors )

SET( INTEFACES_OUTPUT_PATH include/lxqt-core/${MODULE} )
SET( RESOURCES_OUTPUT_PATH shared/lxqt-core/${MODULE} )

set(PROGRAM "dcore")

# Include QT
find_package ( Qt4 4.6.0 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	)



include_directories(
    ${lxqt-core_PATH}/include/lxqt-core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qt4_wrap_cpp(MODULE_MOC_SOURCES ${MODULE_MOCS})
qt4_add_resources(QRC_SOURCES ${MODULE_RESOURCES})
qt4_wrap_ui(FORMS ${MODULE_UIS})


ADD_DEFINITIONS( -DQT_PLUGIN )
ADD_DEFINITIONS( -DQT_SHARED )

# This shuld be enabled in order to try the plugin in 
# a "realease" mode build.
#ADD_DEFINITIONS( -DQT_NO_DEBUG )

add_library(${PROJECT} SHARED 
    ${MODULE_HEADERS}
    ${MODULE_SOURCES}
    ${MODULE_MOC_SOURCES}
    ${FORMS}
    ${QM_FILES}
    ${QRC_SOURCES}
    ${DESKTOP_FILES}

    # Parent
    ${nomain-razor-runner_CPP_FILES} 
    ${razor-runner_UI_FILES} 
    ${razor-runner_QRC_SOURCES} 
    ${razor-runner_QM_FILES} 
    ${razor-runner_MOC_SOURCES}
    )

target_link_libraries(${PROJECT}  ${EXTERNAL_LIBS})

INSTALL(TARGETS ${PROJECT} 
            LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH})

INSTALL(FILES ${MODULE_PUBLIC_INTERFACES} 
    DESTINATION ${INTEFACES_OUTPUT_PATH} )

INSTALL(FILES ${MODULE_RESOURCES} 
    DESTINATION ${RESOURCES_OUTPUT_PATH} )

INSTALL(FILES ${MODULE_DESCRIPTOR} 
    DESTINATION ${DESCRIPTOR_OUTPUT_PATH} )
