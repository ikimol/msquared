# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: cmake :: msq_example.cmake
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# add a new example target
#
# usage: msq_add_example(<name>
#                        SOURCES <src>...
#                        [INCLUDE_DIR <dir>]
#                        [LIBRARIES <lib>...]
#                        [RESOURCE_DIR <dir>]
#                        )
function(msq_add_example EXAMPLE_NAME)
    cmake_parse_arguments(ARG "" "INCLUDE_DIR;RESOURCE_DIR" "SOURCES;LIBRARIES;" ${ARGN})

    set(TARGET_NAME "example-${EXAMPLE_NAME}")

    add_executable(${TARGET_NAME} ${ARG_SOURCES})

    target_include_directories(${TARGET_NAME} PRIVATE ${ARG_INCLUDE_DIR})

    # enable warnings
    msq_target_enable_warnings(${TARGET_NAME})

    target_link_libraries(${TARGET_NAME} msq::engine ${ARG_LIBRARIES})

    if (ARG_RESOURCE_DIR)
        get_filename_component(DIR_NAME ${ARG_RESOURCE_DIR} NAME)
        cmake_path(APPEND CMAKE_CURRENT_BINARY_DIR ${DIR_NAME}
                OUTPUT_VARIABLE DESTINATION_DIR)
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E create_symlink "${ARG_RESOURCE_DIR}" "${DESTINATION_DIR}"
        )
    endif ()
endfunction()
