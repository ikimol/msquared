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
               ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/colors.cpp
               )

# add public header files
target_include_directories(${MSQ_CORE_TARGET_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           )

# add private header files
target_include_directories(${MSQ_CORE_TARGET_NAME} PRIVATE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           )

# ------------------------------------------------------------------------------
# target settings
# ------------------------------------------------------------------------------

msq_target_enable_warnings(${MSQ_CORE_TARGET_NAME})

# add compile definitions

list(APPEND MSQ_CORE_COMPILE_DEFINITIONS
     $<$<CONFIG:Debug>:MSQ_DEBUG>
     )

target_compile_definitions(${MSQ_CORE_TARGET_NAME} PUBLIC
                           ${MSQ_CORE_COMPILE_DEFINITIONS}
                           )

# ------------------------------------------------------------------------------
# installation
# ------------------------------------------------------------------------------
