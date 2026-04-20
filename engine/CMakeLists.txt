# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: engine :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(MSQ_ENGINE_TARGET_NAME "msq-engine")

# ------------------------------------------------------------------------------
# create the library
# ------------------------------------------------------------------------------

add_library(${MSQ_ENGINE_TARGET_NAME} SHARED)

add_library(msq::engine ALIAS ${MSQ_ENGINE_TARGET_NAME})

target_sources(${MSQ_ENGINE_TARGET_NAME} PRIVATE
               ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp
               )

# add public engine header files
target_include_directories(${MSQ_ENGINE_TARGET_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           )

# add private engine header files
target_include_directories(${MSQ_ENGINE_TARGET_NAME} PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           )

# link dependencies
target_link_libraries(${MSQ_ENGINE_TARGET_NAME} PUBLIC
                      msq::core
                      msq::sdl
                      )

# ------------------------------------------------------------------------------
# target settings
# ------------------------------------------------------------------------------

msq_target_enable_warnings(${MSQ_ENGINE_TARGET_NAME})

set_target_properties(${MSQ_ENGINE_TARGET_NAME} PROPERTIES
                      DEBUG_POSTFIX "-d"
                      )

# add compile definitions

list(APPEND MSQ_ENGINE_COMPILE_DEFINITIONS
     $<$<CONFIG:Debug>:MSQ_DEBUG>
     )

target_compile_definitions(${MSQ_ENGINE_TARGET_NAME} PUBLIC
                           ${MSQ_ENGINE_COMPILE_DEFINITIONS}
                           )

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
