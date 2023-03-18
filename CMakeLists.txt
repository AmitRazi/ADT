cmake_minimum_required(VERSION 3.23)
project(untitled9 C)

set(CMAKE_C_STANDARD 99)

set(Headers Person.h book.h AdptArray.h)

add_executable(untitled9 book.c Demo.c Person.c AdptArray.c)
