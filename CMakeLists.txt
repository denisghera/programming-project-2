cmake_minimum_required(VERSION 3.24)
project(pp_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(pp_cpp main.cpp InventoryItem.h Inventory.h Headers.h RecipeItem.h Recipe.h)
