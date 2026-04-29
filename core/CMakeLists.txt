# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: core :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(MSQ_CORE_TARGET_NAME "msq-core")

# ------------------------------------------------------------------------------
# create the library
# ------------------------------------------------------------------------------

add_library(${MSQ_CORE_TARGET_NAME} STATIC)

add_library(msq::core ALIAS ${MSQ_CORE_TARGET_NAME})

target_sources(${MSQ_CORE_TARGET_NAME} PRIVATE
               ${CMAKE_CURRENT_SOURCE_DIR}/src/assert.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/colors.cpp
               )

msq_target_add_public_headers(${MSQ_CORE_TARGET_NAME})
msq_target_add_private_headers(${MSQ_CORE_TARGET_NAME})

# link dependencies
target_link_libraries(${MSQ_CORE_TARGET_NAME} PUBLIC
                      shard::common
                      )

# ------------------------------------------------------------------------------
# target settings
# ------------------------------------------------------------------------------

msq_target_enable_warnings(${MSQ_CORE_TARGET_NAME})
msq_target_set_compile_definitions(${MSQ_CORE_TARGET_NAME})

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
