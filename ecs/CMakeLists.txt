# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: ecs :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(MSQ_ECS_TARGET_NAME "msq-ecs")

# ------------------------------------------------------------------------------
# create the library
# ------------------------------------------------------------------------------

add_library(${MSQ_ECS_TARGET_NAME} STATIC)

add_library(msq::ecs ALIAS ${MSQ_ECS_TARGET_NAME})

target_sources(${MSQ_ECS_TARGET_NAME} PRIVATE
               ${CMAKE_CURRENT_SOURCE_DIR}/src/archetype.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/archetype_registry.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/entity_archetype_map.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/component_mask.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/component_registry.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/entity.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/entity_index_map.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/entity_pool.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/query_cache.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/world.cpp
               )

msq_target_add_public_headers(${MSQ_ECS_TARGET_NAME})
msq_target_add_private_headers(${MSQ_ECS_TARGET_NAME})

# link dependencies
target_link_libraries(${MSQ_ECS_TARGET_NAME} PUBLIC
                      msq::core
                      shard::memory
                      shard::meta
                      shard::utility
                      )

# ------------------------------------------------------------------------------
# target settings
# ------------------------------------------------------------------------------

msq_target_enable_warnings(${MSQ_ECS_TARGET_NAME})
msq_target_set_compile_definitions(${MSQ_ECS_TARGET_NAME})

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
