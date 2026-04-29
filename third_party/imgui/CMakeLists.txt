# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# msquared :: third_party :: imgui :: CMakeLists.txt
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

set(IMGUI_LIB_NAME ImGui)

add_library(${IMGUI_LIB_NAME} STATIC)

add_library(ImGui::ImGui ALIAS ${IMGUI_LIB_NAME})

target_sources(${IMGUI_LIB_NAME} PRIVATE
               # -- core
               ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_demo.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_draw.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_tables.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_widgets.cpp
               # -- misc
               ${CMAKE_CURRENT_SOURCE_DIR}/src/misc/cpp/imgui_stdlib.cpp
               # -- backend
               ${CMAKE_CURRENT_SOURCE_DIR}/src/backends/imgui_impl_sdl3.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/backends/imgui_impl_sdlrenderer3.cpp
               )

target_include_directories(${IMGUI_LIB_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE:include>
                           )

target_link_libraries(${IMGUI_LIB_NAME} PRIVATE
                      SDL3::SDL3
                      )
