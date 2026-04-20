# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: tests :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(MSQ_TEST_TARGET_NAME "tests")

add_executable(${MSQ_TEST_TARGET_NAME}
               ${CMAKE_CURRENT_SOURCE_DIR}/dummy_tests.cpp
               )

target_link_libraries(${MSQ_TEST_TARGET_NAME} PRIVATE
                      Catch2::Catch2WithMain
                      )

# add CTest compatibility

list(APPEND CMAKE_MODULE_PATH "${MSQ_CMAKE_THIRD_PARTY_DIR}/catch2/extras")

include(Catch)

catch_discover_tests(${MSQ_TEST_TARGET_NAME})
