cmake_minimum_required(VERSION 3.16)
project(sirius_interpreter)


file(GLOB SHARED_SRC src/*.cpp)


add_executable(sirius_interpreter main.cpp ${SHARED_SRC})
target_include_directories(sirius_interpreter PRIVATE include)


if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_options(sirius_interpreter PRIVATE -Wall -Wextra -Werror -O1 -fno-omit-frame-pointer -fno-limit-debug-info -fsanitize=address,undefined)
    target_link_options(sirius_interpreter PRIVATE -fsanitize=address,undefined)
else ()
    target_compile_options(sirius_interpreter PRIVATE -Wall -Wextra -Werror -O3 -mavx2)
endif ()

