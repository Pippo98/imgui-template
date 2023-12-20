cmake_minimum_required(VERSION 3.16)
project(imgui-template)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -O3 -std=c++2a")
add_compile_definitions("ImDrawIdx=unsigned int")
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

find_package(GLEW      REQUIRED)
find_package(OpenGL    REQUIRED)
find_package(glfw3 3.3 REQUIRED)

if (NOT GLEW_LIBRARIES)
    if (GLEW_LIBRARY_DEBUG AND GLEW_LIBRARY_RELEASE)
        set(GLEW_LIBRARIES "optimized;${GLEW_LIBRARY_RELEASE};debug;${GLEW_LIBRARY_DEBUG}")
    else ()
        set(GLEW_LIBRARIES GLEW::GLEW)
    endif ()
endif ()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    
    # thirdparty
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/imgui/misc/cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/implot

    # GLEW
    ${GLEW_INCLUDE_DIRS}
)

FILE(GLOB imgui_srcs ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/imgui/*)
FILE(GLOB implot_srcs ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/implot/*)

add_library(
    imgui
    STATIC

    # GUI
    ${imgui_srcs}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/imgui/misc/cpp/imgui_stdlib.cpp
)

add_library(
    implot
    STATIC
    
    # PLOT
    ${implot_srcs}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/implot/implot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/thirdparty/implot/implot_items.cpp
)

target_link_libraries(
    imgui

    glfw
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)
target_link_libraries(
    implot

    imgui
    glfw
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(
    ${PROJECT_NAME}_example_1

    ${CMAKE_CURRENT_SOURCE_DIR}/examples/example_1.cpp
)
target_link_libraries(
    ${PROJECT_NAME}_example_1

    imgui
    implot
)

add_executable(
    ${PROJECT_NAME}_example_app

    ${CMAKE_CURRENT_SOURCE_DIR}/examples/example_app.cpp
)
target_link_libraries(
    ${PROJECT_NAME}_example_app

    imgui
    implot
)