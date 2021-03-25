cmake_minimum_required(VERSION 3.16)
project(BoxerUI)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
find_package(glfw3 3.3.2 REQUIRED)

set(PROJECT_DIR "/home/username/Documents/BoxerUI/BoxerUI/header")
set(IMGUI_DIR "${PROJECT_DIR}/imgui/" )
    set(IMGUI_SOURCES  "${IMGUI_DIR}imgui.cpp" "${IMGUI_DIR}imgui_demo.cpp" "${IMGUI_DIR}imgui_draw.cpp" "${IMGUI_DIR}imgui_tables.cpp" 
    "${IMGUI_DIR}imgui_widgets.cpp")

set(IMGUI_BACKENDS_DIR "${IMGUI_DIR}backends/")
    set(IMGUI_BACKENDS_SOURCES "${IMGUI_BACKENDS_DIR}imgui_impl_glfw.cpp" "${IMGUI_BACKENDS_DIR}imgui_impl_opengl3.cpp")
set(IMGUI_EXAMPLES_LIBS_SOURCES "${IMGUI_DIR}examples/libs/gl3w/GL/gl3w.c" )
set(IMPLOT_DIR "${PROJECT_DIR}/implot/")
    set(IMPLOT_SOURCES "${IMPLOT_DIR}implot.cpp" "${IMPLOT_DIR}implot_demo.cpp" "${IMPLOT_DIR}implot_items.cpp")

set(SOURCE "/home/username/Documents/BoxerUI/BoxerUI/src/main.cpp" "${IMGUI_SOURCES}" "${IMGUI_BACKENDS_SOURCES}" "${IMPLOT_SOURCES}" 
"${IMGUI_EXAMPLES_LIBS_SOURCES}"  )

add_executable(BoxerUI_app "${SOURCE}")

target_include_directories(BoxerUI_app PUBLIC "${IMGUI_DIR}" "${IMGUI_BACKENDS_DIR}" "${IMPLOT_DIR}" "${IMGUI_DIR}examples/libs/gl3w/" 
"${IMPLOT_DIR}" "/home/username/Documents/BoxerUI/BoxerUI/header/imgui/examples/libs/glfw/include/GLFW/") 
# "${IMGUI_DIR}examples/libs/glfw/include/GLFW/"  )
# target_link_libraries(BoxerUI_app glfw)
find_package(OpenGL REQUIRED)

target_link_libraries( BoxerUI_app PUBLIC "${CMAKE_DL_LIBS}" glfw "${OpenCV_LIBS}" OpenGL::GL  )#"GL" "pkg-config --static --libs= ${IMGUI_EXAMPLES_LIBS_SOURCES}")