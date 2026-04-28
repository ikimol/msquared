# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: sdl :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(MSQ_SDL_TARGET_NAME "msq-sdl")

# ------------------------------------------------------------------------------
# create the library
# ------------------------------------------------------------------------------

add_library(${MSQ_SDL_TARGET_NAME} STATIC)

add_library(msq::sdl ALIAS ${MSQ_SDL_TARGET_NAME})

target_sources(${MSQ_SDL_TARGET_NAME} PRIVATE
               ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp
               )

# add public header files
target_include_directories(${MSQ_SDL_TARGET_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           )

# add private header files
target_include_directories(${MSQ_SDL_TARGET_NAME} PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           )

# link dependencies
target_link_libraries(${MSQ_SDL_TARGET_NAME} PUBLIC
                      SDL3::SDL3
                      SDL3_ttf::SDL3_ttf
                      )

# ------------------------------------------------------------------------------
# target settings
# ------------------------------------------------------------------------------

msq_target_enable_warnings(${MSQ_SDL_TARGET_NAME})

# add compile definitions

list(APPEND MSQ_SDL_COMPILE_DEFINITIONS
     $<$<CONFIG:Debug>:MSQ_DEBUG>
     )

target_compile_definitions(${MSQ_SDL_TARGET_NAME} PUBLIC
                           ${MSQ_SDL_COMPILE_DEFINITIONS}
                           )

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
