cmake_minimum_required (VERSION 3.12)
project (
  "28_model_loading"
  VERSION 2.0.0
  DESCRIPTION "A game engine using the Vulkan API"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-D IMGUI_IMPL_VULKAN_NO_PROTOTYPES)
add_compile_options(-Wno-nullability-completeness)
add_compile_options(-D_CRT_SECURE_NO_WARNINGS) #for assimp

find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${DSL2_INCLUDE_DIRS})

set(VULKAN $ENV{VULKAN_SDK}) #set to Vulkan SDK

set(BUILD ${PROJECT_SOURCE_DIR}/build)  # engine include directory
set(INCLUDE ${PROJECT_SOURCE_DIR}/include)  # engine include directory

# ---- Begin Fetch ImGui ---
include(FetchContent) # enable Fetch Content

FetchContent_Declare(imgui
                     GIT_REPOSITORY https://github.com/ocornut/imgui.git 
                     GIT_TAG master)
FetchContent_MakeAvailable(Imgui)

set(IMGUI ${imgui_SOURCE_DIR})

# --- End Fetch ImGui

set(TARGET 28_model_loading)

add_subdirectory(volk)

set(SOURCE
  ${IMGUI}/imgui.cpp
  ${IMGUI}/imgui_demo.cpp
  ${IMGUI}/imgui_draw.cpp
  ${IMGUI}/backends/imgui_impl_sdl2.cpp
  ${IMGUI}/backends/imgui_impl_vulkan.cpp
  ${IMGUI}/imgui_tables.cpp
  ${IMGUI}/imgui_widgets.cpp
  28_model_loading.cpp
  )

set(HEADERS )

add_executable(${TARGET} ${SOURCE} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE volk)

target_include_directories(${TARGET} PUBLIC stb)
target_include_directories(${TARGET} PUBLIC ${VULKAN}/Include)
target_include_directories(${TARGET} PUBLIC ${VULKAN}/Include/SDL2)
target_include_directories(${TARGET} PUBLIC ${VULKAN}/Include/Volk)
target_include_directories(${TARGET} PUBLIC ${VULKAN}/Include/glm)
target_include_directories(${TARGET} PUBLIC ${VULKAN}/Include/vma)
target_include_directories(${TARGET} PUBLIC ${IMGUI})
target_include_directories(${TARGET} PUBLIC ${IMGUI}/backends)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})