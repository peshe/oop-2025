cmake_minimum_required(VERSION 3.31)
project(cpp_20250417)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_20250417 main.cpp Bank.cpp Bank.hpp Client.cpp Client.hpp ConversionRate.hpp Currency.hpp Date.cpp Date.hpp Money.cpp Money.hpp)
