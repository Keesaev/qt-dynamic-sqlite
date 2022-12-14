cmake_minimum_required(VERSION 3.5)

project(qt-dynamic-sqlite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

include_directories(${SQLite3_INCLUDE_DIRS})

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.qrc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db/cache/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db/cache/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db/cache/*.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    SQLite::SQLite3
)

