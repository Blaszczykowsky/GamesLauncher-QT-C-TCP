cmake_minimum_required(VERSION 3.16)
project(WisielecStandalone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(WisielecStandalone
    main.cpp
    mainwindow.h
    mainwindow.cpp
    game_logic.h
    game_logic.cpp
)

target_link_libraries(WisielecStandalone PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
