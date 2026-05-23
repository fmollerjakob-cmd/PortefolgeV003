cmake_minimum_required(VERSION 3.16)

project(PortefolgeV003)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

add_executable(PortefolgeV003 
    main.cpp
    Monster.cpp
    character.cpp
    Game.cpp
    Item.cpp
    Grotte.cpp
    Database.cpp
)


target_link_libraries(PortefolgeV003
    SQLite::SQLite3
)

