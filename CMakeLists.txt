cmake_minimum_required(VERSION 3.5)

project(shapes LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS OpenGLWidgets Widgets REQUIRED)

set(PROJECT_SOURCES
  src/main.cpp
  src/main_window.cpp
  src/main_window.h
  src/shape.cpp
  src/shape.h
  src/shape_widget.cpp
  src/shape_widget.h
)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
qt_add_executable(shapes
  ${PROJECT_SOURCES}
)

#add_executable(shapes
#  ${PROJECT_SOURCES}
#)

target_link_libraries(shapes PRIVATE
  Qt6::OpenGLWidgets
  Qt6::Widgets
)
