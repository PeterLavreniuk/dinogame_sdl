cmake_minimum_required(VERSION 3.17)
project(dinogame)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED SDL2)

add_executable(dinogame src/main.cpp src/Dino.h src/Dino.cpp src/DummySprite.h src/DummySprite.cpp src/Cactus.h src/Cactus.cpp src/CactusFactory.h src/CactusFactory.cpp)

target_link_libraries(dinogame PRIVATE SDL2 SDL2_image)