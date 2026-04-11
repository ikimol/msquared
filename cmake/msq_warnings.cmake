# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: cmake :: msq_warnings.cmake
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
