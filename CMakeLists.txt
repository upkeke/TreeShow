cmake_minimum_required(VERSION 3.5)

project(TreeShow VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        #WIN32
        main.cpp
        mainwin.cpp
        mainwin.h
        mainwin.ui
        AVTree.h
        AVTree.cpp
        MyGraphicsItem.h
        MyGraphicsItem.cpp
 "MyLineItem.h" "MyLineItem.cpp")
add_executable(TreeShow  ${PROJECT_SOURCES})

target_link_libraries(TreeShow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

#[[
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set (CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\msvc2019_64\\")


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

SET(CMAKE_BUILD_TYPE DEBUG)

set(PROJECT_SOURCES
        #WIN32
        head.h
        main.cpp
        mainwin.cpp
        mainwin.h
        mainwin.ui
        AVTree.h
        AVTree.cpp
        MyGraphicsItem.h
        MyGraphicsItem.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TreeShow
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TreeShow APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TreeShow SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(TreeShow
            ${PROJECT_SOURCES}
            "img/res.qrc" "img/fang1.png")
    endif()
endif()

target_link_libraries(TreeShow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TreeShow PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)



target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TreeShow)
endif()

]]#