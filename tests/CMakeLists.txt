# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: tests :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(MSQ_TEST_TARGET_NAME "tests")

add_executable(${MSQ_TEST_TARGET_NAME}
               # -- core
               ${CMAKE_CURRENT_SOURCE_DIR}/core/event_queue_tests.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/core/math_tests.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/core/rect2_tests.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/core/size2_tests.cpp
               )

target_link_libraries(${MSQ_TEST_TARGET_NAME} PRIVATE
                      msq::core
                      msq::engine
                      Catch2::Catch2WithMain
                      )

# add CTest compatibility

list(APPEND CMAKE_MODULE_PATH "${MSQ_CMAKE_THIRD_PARTY_DIR}/catch2/extras")

include(Catch)

catch_discover_tests(${MSQ_TEST_TARGET_NAME})
