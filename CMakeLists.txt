cmake_minimum_required(VERSION 3.20)
project(steganografia_obrazowa)

set(CMAKE_CXX_STANDARD 17)

add_executable(steganografia_obrazowa Pixel.h steganography.h main.cpp bmp.h png.h channels.h)
