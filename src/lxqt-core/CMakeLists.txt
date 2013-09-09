find_package ( Qt4 REQUIRED )

set(PROJECT lxqt-core)

if (NOT CMAKE_INSTALL_PREFIX)
    message(FATAL_ERROR "CMAKE_INSTALL_PREFIX is not set but it has to be. Something is wrong.")
endif ()

include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTXML_INCLUDE_DIR} ${QT_QTDBUS_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}
	src)

set ( ${PROJECT}_SRCS 
	main.cpp
        ModuleFactory.cpp
        Core.cpp
        
        ModuleDescriptor.cpp
	)

configure_file( lxqt-core-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/lxqt-core-config.h)
set ( ${PROJECT}_HEADERS 
    LxqtModuleInterface.h
    ModuleFactory.h
    Core.h
    ModuleDescriptor.h
    lxqt-core-config.h
)

# The followin headers will be installed with the application
set ( ${PROJECT}_PUBLIC_HEADERS 
    LxqtModuleInterface.h
    ModuleDescriptor.h
    Core.h
)

set ( ${PROJECT}_MOCS
)

set (${PROJECT}_UIS
)

set ( ${PROJECT}_RESOURCES
)

# Include QT
find_package ( Qt4 4.6.0 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	)

qt4_wrap_cpp(${PROJECT}_HEADERS_MOC ${${PROJECT}_MOCS})
qt4_add_resources(${PROJECT}_QRC_SOURCES ${${PROJECT}_RESOURCES})
qt4_wrap_ui(${PROJECT}_UI_HEADERS ${${PROJECT}_UIS})

add_executable ( ${PROJECT} 
    ${${PROJECT}_SRCS} 
    ${${PROJECT}_HEADERS}
    
    ${${PROJECT}_HEADERS_MOC}
    ${${PROJECT}_QRC_SOURCES}
    ${${PROJECT}_UI_HEADERS}
    
    ${${PROJECT}_PUBLIC_HEADERS} )

target_link_libraries ( ${PROJECT}  
    ${QT_QTCORE_LIBRARY} 
    ${QT_QTGUI_LIBRARY} 
    ${QT_QTXML_LIBRARY} 
    ${QT_QTDBUS_LIBRARY} 

    razorqt
    qtxdg
)

# Install public header
INSTALL(FILES ${${PROJECT}_PUBLIC_HEADERS} DESTINATION include/${PROJECT} )
INSTALL(TARGETS ${PROJECT}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)