# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: examples :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

include(msq_filesystem)

msq_list_subdirs(EXAMPLE_DIRS ${CMAKE_CURRENT_LIST_DIR})

foreach (EXAMPLE_DIR ${EXAMPLE_DIRS})
    add_subdirectory(${EXAMPLE_DIR})
endforeach ()
