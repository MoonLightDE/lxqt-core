cmake_minimum_required(VERSION 2.8)

PROJECT( LXQT-CORE )


SET(CMAKE_BUILD_TYPE Debug)
#SET(CMAKE_BUILD_TYPE Release)

# Uncoment the following lines to use the clang compiler 
#set(DCMAKE_C_COMPILER clang)
#set(DCMAKE_CXX_COMPILER clang++)

SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )


find_package ( Qt4 4.6.0 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	)

ADD_SUBDIRECTORY( lxqt-core )
ADD_SUBDIRECTORY( lxqt-modules )