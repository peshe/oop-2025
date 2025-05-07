cmake_minimum_required(VERSION 4.0)
project(oop_20250507)

set(CMAKE_CXX_STANDARD 20)

add_executable(oop_20250507 main.cpp
        StringHelpers.hpp
        Furniture.cpp
        Furniture.hpp
        Table.cpp
        Table.hpp
        Chair.cpp
        Chair.hpp
        Bed.cpp
        Bed.hpp
        AbstractFurnitureCatalog.hpp
        InMemoryFurnitureCatalog.cpp
        InMemoryFurnitureCatalog.hpp
)
