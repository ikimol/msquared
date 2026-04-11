# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: cmake :: msq_filesystem.cmake
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# get the subdirectories of the given directory
#
# usage: msq_list_subdirs(DIRS ${CMAKE_CURRENT_LIST_DIR})
function(msq_list_subdirs OUT_DIRECTORIES DIRECTORY)
    file(GLOB CHILDREN RELATIVE ${DIRECTORY} ${DIRECTORY}/*)
    foreach (CHILD ${CHILDREN})
        if (IS_DIRECTORY ${DIRECTORY}/${CHILD})
            list(APPEND DIRECTORY_LIST ${CHILD})
        endif ()
    endforeach ()
    set(${OUT_DIRECTORIES} ${DIRECTORY_LIST} PARENT_SCOPE)
endfunction()