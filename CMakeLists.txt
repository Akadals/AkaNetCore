cmake_minimum_required(VERSION 3.20)
project(
    LyntraNet
    VERSION 0.5.1
    LANGUAGES CXX
)
set(LyntraNet_VERSION_TAG "dev")
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/LyntraNet/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/Version.h
    @ONLY
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_library(LyntraNet STATIC
    ${SOURCES}
)

target_include_directories(LyntraNet
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)

if(WIN32)
    target_compile_definitions(LyntraNet
        PRIVATE
            WIN32_LEAN_AND_MEAN
            NOMINMAX
    )

    target_link_libraries(LyntraNet
        ws2_32
        mswsock
    )
endif()

target_precompile_headers(LyntraNet
    PRIVATE
        src/pch.h
)

# ----------------------------
# Tests
# ----------------------------

enable_testing()
add_subdirectory(tests)

