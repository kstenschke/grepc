cmake_minimum_required(VERSION 3.10)
project(grepc)

set(CMAKE_CXX_STANDARD 14)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/mac)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/linux)
endif()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(grepc grepc/main.cc)

install(TARGETS
        ${PROJECT_NAME}
        RUNTIME DESTINATION /usr/bin/)
