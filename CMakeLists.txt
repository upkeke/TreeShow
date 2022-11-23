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

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)


# 添加资源文件
#file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
#set(QRC_SOURCE_FILES res.qrc)
#qt5_add_resources(QRC_FILES  ${QRC_SOURCE_FILES})




set(PROJECT_SOURCES
        #WIN32
        main.cpp
        ${QRC_FILES}
        mainwin.cpp
        mainwin.h
        mainwin.ui
        "AVLTree.h" "AVLTree.cpp"
        "MyGraphicsItem.h" "MyGraphicsItem.cpp"
        "MyLineItem.h" "MyLineItem.cpp"
  "RBTree.h" "RBTree.cpp"
   "Tree.h" "Tree.cpp"
  )
add_executable(TreeShow  ${PROJECT_SOURCES})

target_link_libraries(TreeShow PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

