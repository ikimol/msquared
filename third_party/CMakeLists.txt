# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: third_party :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

add_subdirectory(catch2)

if (MSQ_USE_VENDORED_SDL)
    add_subdirectory(sdl)
    add_subdirectory(sdl_image)
    add_subdirectory(sdl_ttf)
endif ()
