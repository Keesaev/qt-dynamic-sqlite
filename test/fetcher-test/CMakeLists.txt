cmake_minimum_required(VERSION 3.5)

project(fetcher-test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.qrc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fetcher/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fetcher/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fetcher/*.cpp
)


add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
