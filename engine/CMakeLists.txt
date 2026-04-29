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
               ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui/interop.cpp
               )

msq_target_add_public_headers(${MSQ_ENGINE_TARGET_NAME})
msq_target_add_private_headers(${MSQ_ENGINE_TARGET_NAME})

# link dependencies
target_link_libraries(${MSQ_ENGINE_TARGET_NAME} PUBLIC
                      msq::core
                      msq::sdl
                      ImGui
                      )

# ------------------------------------------------------------------------------
# target settings
# ------------------------------------------------------------------------------

msq_target_enable_warnings(${MSQ_ENGINE_TARGET_NAME})
msq_target_set_compile_definitions(${MSQ_ENGINE_TARGET_NAME})

set_target_properties(${MSQ_ENGINE_TARGET_NAME} PROPERTIES
                      DEBUG_POSTFIX "-d"
                      )

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
