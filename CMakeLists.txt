
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(libejovo++)

# find_library(matplot REQUIRED)
include(FindPNG)
include(FindGnuplot)
include(GNUInstallDirs)

find_package(GTest)

include(GoogleTest)

enable_testing(ON)


enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(matrix++ INTERFACE)

set(PROJ_INC ${PROJECT_SOURCE_DIR}/include)
set(PROJ_TEST ${PROJECT_SOURCE_DIR}/test)
set(PROJ_SRC ${PROJECT_SOURCE_DIR}/src)

target_include_directories(matrix++ INTERFACE ${PROJ_INC})
add_compile_options(-Wno-narrowing)
add_compile_options($<$<CONFIG:Release>:-O3>)
add_compile_options(-Wall -Wunused-result)

add_subdirectory(${PROJ_SRC})
add_subdirectory(${PROJ_TEST})