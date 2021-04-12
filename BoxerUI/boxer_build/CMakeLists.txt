cmake_minimum_required(VERSION 3.16)
project(BoxerUI)

#Note: Shared/dynamic libraries are linked at runtime (must be included with obj/binary file), static are linked at compile time (larger file size).

find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    set(BUILD_SHARED_LIBS OFF)
    set(OpenCV_STATIC ON)#just to make sure
    # set(OpenCV_DIR "/usr/local/include/")

find_package(OpenGL REQUIRED)
    # find_package(glfw3 3.3.2 REQUIRED) #for shared library linking. Use "sudo apt-get install libglfw3-dev" to download the shared lib

#The 3 following lines ask not to build glfw docs, tests, & examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Source dir and files variables
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
"${IMGUI_EXAMPLES_LIBS_SOURCES}")

#Should print the include dir and link libs.
MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

add_subdirectory("/home/username/Documents/glfw/" "/home/username/Documents/glfw-build/")# Runs the CMakeLists.txt in source_dir and places the output in binary_dir
# add_subdirectory("/home/username/opencv-master" "/home/username/opencv-build") #Attempt at using setup as for glfw. works haven't figured out how to build static for just modules req, & what the link target is
# add_library(glfw3 STATIC "${IMGUI_DIR}examples/libs/glfw/include/GLFW/glfw3.h")#uses gl3w file included. might be old. ALso this alternative doesn't work
#adds the dir for src files when compiling. Allows cmake to find where header files are located
include_directories("${IMGUI_DIR}" "${IMGUI_BACKENDS_DIR}" "${IMPLOT_DIR}" "${IMGUI_DIR}examples/libs/gl3w/" 
# "/home/username/opencv-master/modules/"
    "${OpenCV_INCLUDE_DIRS}"
    # "/usr/local/include/opencv4/"
      "${IMPLOT_DIR}")
#Executable target name and src files
add_executable(BoxerUI_app "${SOURCE}")
#Links the libraries to build target set in add_executable command
target_link_libraries(BoxerUI_app  OpenGL::GL glfw "${OpenCV_LIBS}"  )

#To link glfw statically:
    #1. clone the repo into a directory <glfw_dir>: "git clone https://github.com/glfw/glfw.git"
    #2. make & select a build dir: "mkdir ./glfw-build/;cd glfw-build; cmake ../<glfw_dir>/"
    #3. !!WARNING!!. sudo make install will globally. add_subdirectory() command line 38 should avoid this.

#To link opencv statically: (For reference on configuring your build: https://docs.opencv.org/master/db/d05/tutorial_config_reference.html)
    #1. Get and unzip opencv: "wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip; unzip opencv.zip"
    #2. Build opencv: "cmake ../opencv-master/ -DBUILD_TESTS=OFF -DBUILD_opencv_python2=OFF -DBUILD_opencv_python3=OFF
                        # -DWITH_OPENEXR=OFF -DWITH_1394=OFF -DWITH_EIGEN=OFF -DWITH_OPENGL=ON
                        # -DBUILD_SHARED_LIBS=OFF -DWITH_FFMPEG=OFF ." FFMPEG could be useful: Investigate
        #2-a. More modifiable values can be found: "cmake -LH" or "cmake -L"
        #2-b. "sudo make install" will install globally. i.e. in /usr/... "make -j2" to compile in parallel (Faster install)
        #2-c. You can indicate specific modules you'll like to build e.g. "-DBUILD_opencv_python2=OFF"
    #3. Visit "cat OpenCVConfig.cmake" to view settings and variables as well as tips on including opencv to your project.
    #4. "opencv_version" to find version.
    #5. By default OpenCV will be installed to the /usr/local directory, all files will be copied to following locations:
        # /usr/local/bin - executable files
        # /usr/local/lib - libraries (.so)
        # /usr/local/cmake/opencv4 - cmake package
        # /usr/local/include/opencv4 - headers
        # /usr/local/share/opencv4 - other files (e.g. trained cascades in XML format)

# message(STATUS "${OpenCV_INCLUDE_DIRS}")
