# _lxqt-core module build script #
#TODO: Add internationalization support

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

# Use the name of the main module class 
# You must set this name also to te folder.

set(MODULE "LxqtMod_CoreConfig")

set(${MODULE}_HEADERS
    ${MODULE}.h
    basicsettings.h
    modulemodel.h
)

set(${MODULE}_PUBLIC_INTERFACES
    ${MODULE}.h
)


set(${MODULE}_SOURCES
    ${MODULE}.cpp
    basicsettings.cpp
    modulemodel.cpp
)

set(${MODULE}_MOCS
    ${MODULE}.h
    basicsettings.h
    modulemodel.h

)

set(${MODULE}_UIS
    basicsettings.ui
)

set(${MODULE}_RESOURCES
)

# Edit the module descriptor template
configure_file( Descriptor.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}.desktop )
set(${MODULE}_DESCRIPTOR
    ${CMAKE_CURRENT_BINARY_DIR}/${MODULE}.desktop
)


# Include libs
set(EXTERNAL_LIBS

    ${LIBRARIES}
#   Remember to always include the Qt Libraries
#   ${QT_LIBRARIES}
)

# Include parenth files 
set ( ${MODULE}_PARENT_FILES
)



#*******************************************#
#       Don't modify the code below         #
#*******************************************#

set(PROJECT "${MODULE}")
project(${PROJECT})



SET( LIBRARY_OUTPUT_PATH lib/lxqt-core/modules )
SET( DESCRIPTOR_OUTPUT_PATH share/lxqt-core/descriptors )

SET( INTERFACES_OUTPUT_PATH include/lxqt-core/${MODULE} )
SET( RESOURCES_OUTPUT_PATH shared/lxqt-core/${MODULE} )

# Include QT
find_package ( Qt4 4.6.0 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	)



include_directories(
    ${CMAKE_INSTALL_PREFIX}/include/lxqt-core
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qt4_wrap_cpp(${MODULE}_MOC_SOURCES ${${MODULE}_MOCS})
qt4_add_resources(${MODULE}_QRC_SOURCES ${${MODULE}_RESOURCES})
qt4_wrap_ui(${MODULE}_UI_HEADERS ${${MODULE}_UIS})


ADD_DEFINITIONS( -DQT_PLUGIN )
ADD_DEFINITIONS( -DQT_SHARED )

# This shuld be enabled in order to try the plugin in 
# a "realease" mode build.
#ADD_DEFINITIONS( -DQT_NO_DEBUG )

# Exclude main.cpp from compilation
foreach(item ${${MODULE}_PARENT_FILES} )
    if(NOT item MATCHES "main.cpp")
        SET ( ${MODULE}_FINAL_PARENT_FILES
            ${${MODULE}_FINAL_PARENT_FILES}
            ${item} )
    endif(NOT item MATCHES "main.cpp")

endforeach(item)


add_library(${PROJECT} SHARED
    ${${MODULE}_HEADERS}
    ${${MODULE}_SOURCES}
    ${${MODULE}_QRC_SOURCES}
    ${${MODULE}_MOC_SOURCES}
    ${${MODULE}_UI_HEADERS}

    # Parent
    ${${MODULE}_FINAL_PARENT_FILES}
    )

target_link_libraries(${PROJECT}  ${EXTERNAL_LIBS})

INSTALL(TARGETS ${PROJECT} 
            LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH})

INSTALL(FILES ${${MODULE}_PUBLIC_INTERFACES} 
    DESTINATION ${INTERFACES_OUTPUT_PATH} )

INSTALL(FILES ${${MODULE}_RESOURCES} 
    DESTINATION ${RESOURCES_OUTPUT_PATH} )

INSTALL(FILES ${${MODULE}_DESCRIPTOR} 
    DESTINATION ${DESCRIPTOR_OUTPUT_PATH} )
