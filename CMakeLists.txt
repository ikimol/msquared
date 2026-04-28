# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

# ------------------------------------------------------------------------------
# project information
# ------------------------------------------------------------------------------

set(MSQ_VERSION 0.1.0)

project(msquared VERSION ${MSQ_VERSION})

message(STATUS "Building ${PROJECT_NAME} (${PROJECT_VERSION})")

set(CMAKE_CXX_STANDARD 17)

# ------------------------------------------------------------------------------
# system information
# ------------------------------------------------------------------------------

math(EXPR MSQ_SYSTEM_ARCH "${CMAKE_SIZEOF_VOID_P} * 8")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION} (${MSQ_SYSTEM_ARCH}-bit)")

# ------------------------------------------------------------------------------
# build options
# ------------------------------------------------------------------------------

option(MSQ_USE_VENDORED_SDL "Enable to use the vendored SDL libraries" OFF)
option(MSQ_BUILD_EXAMPLES "Enable to build the example targets" OFF)
option(MSQ_BUILD_TESTS "Enable to build the tests" OFF)

# ------------------------------------------------------------------------------
# custom CMake scripts
# ------------------------------------------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(msq_warnings)

# ------------------------------------------------------------------------------
# third party libraries
# ------------------------------------------------------------------------------

if (NOT MSQ_USE_VENDORED_SDL)
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
    find_package(SDL3_image REQUIRED CONFIG REQUIRED)
    find_package(SDL3_ttf REQUIRED CONFIG REQUIRED)
endif ()

# build third party libraries
add_subdirectory(third_party)

# ------------------------------------------------------------------------------
# predefined variables
# ------------------------------------------------------------------------------

set(MSQ_CMAKE_THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# ------------------------------------------------------------------------------
# create targets
# ------------------------------------------------------------------------------

# add core library
add_subdirectory(core)

# add SDL utility library
add_subdirectory(sdl)

# add examples
if (MSQ_BUILD_EXAMPLES)
    include(msq_example)
    add_subdirectory(examples)
endif ()

# add tests
if (MSQ_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
