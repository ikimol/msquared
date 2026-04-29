# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: cmake :: msq_target.cmake
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# add public headers to the given target
function(msq_target_add_public_headers TARGET)
    target_include_directories(${TARGET} PUBLIC
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                               $<INSTALL_INTERFACE:include>
                               )
endfunction()

# add private headers to the given target
function(msq_target_add_private_headers TARGET)
    target_include_directories(${TARGET} PRIVATE
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                               )
endfunction()

# enable warnings for the given target
function(msq_target_enable_warnings TARGET)
    if (MSVC)
        target_compile_options(${TARGET} PRIVATE /W4 /WX)
    else ()
        target_compile_options(${TARGET} PRIVATE
                               -Wall
                               -Wextra
                               -Wpedantic
                               -Werror
                               )
    endif ()
endfunction()

# set the default compile definitions for the given target
function(msq_target_set_compile_definitions TARGET)
    target_compile_definitions(${TARGET} PRIVATE
                               $<$<CONFIG:Debug>:MSQ_DEBUG>
                               )
endfunction()
