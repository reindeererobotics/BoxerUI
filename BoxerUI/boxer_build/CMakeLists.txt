cmake_minimum_required(VERSION 3.16)
project(BoxerUI)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE Release)
find_package(OpenCV REQUIRED)
    # set(OpenCV_DIR "/usr/local/include/")
find_package(glfw3 3.3.2 REQUIRED)
find_package(OpenGL REQUIRED)

# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# add_subdirectory("/usr/local/lib/")

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

set(Boxer_Lib "/usr/local/lib/libopencv_videoio.so.4.2" "/usr/local/lib/libopencv_imgproc.so.4.2" "/usr/local/lib/libopencv_core.so.4.2" "/usr/lib/x86_64-linux-gnu/libglfw.so.3" )
# add_library(gl3w STATIC "${IMGUI_EXAMPLES_LIBS_SOURCES}" )
# add_dependencies(Boxer_Lib "/usr/lib/x86_64-linux-gnu/libglfw.so.3")

include_directories("${IMGUI_DIR}" "${IMGUI_BACKENDS_DIR}" "${IMPLOT_DIR}" "${IMGUI_DIR}examples/libs/gl3w/" #"/usr/local/include/opencv4/"
"${IMPLOT_DIR}" "${OpenCV_INCLUDE_DIRS}"  ) 
add_executable(BoxerUI_app "${SOURCE}" )
# target_link_libraries(BoxerUI_app glfw)
link_directories("")
# link_libraries("${Boxer_Lib}")
target_link_libraries( BoxerUI_app  "${OpenCV_LIBS}" OpenGL::GL glfw  "${CMAKE_DL_LIBS}"    )
# install(FILES "build/libglfw.so.3" "build/libopencv_videoio.so.4.2" "build/libopencv_imgproc.so.4.2" "build/libopencv_core.so.4.2" 
#         DESTINATION "/usr/lib/x86_64-linux-gnu/"
#         CONFIGURATIONS Release)
#"/usr/local/lib/libopencv_videoio.so.4.2"
#"GL" "pkg-config --static --libs= ${IMGUI_EXAMPLES_LIBS_SOURCES}")