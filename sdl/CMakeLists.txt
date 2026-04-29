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
               ${CMAKE_CURRENT_SOURCE_DIR}/src/iostream.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/surface.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/text.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/text_engine.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp
               )

msq_target_add_public_headers(${MSQ_SDL_TARGET_NAME})
msq_target_add_private_headers(${MSQ_SDL_TARGET_NAME})

# link dependencies
target_link_libraries(${MSQ_SDL_TARGET_NAME} PUBLIC
                      SDL3::SDL3
                      SDL3_ttf::SDL3_ttf
                      )

# ------------------------------------------------------------------------------
# target settings
# ------------------------------------------------------------------------------

msq_target_enable_warnings(${MSQ_SDL_TARGET_NAME})
msq_target_set_compile_definitions(${MSQ_SDL_TARGET_NAME})

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
