cmake_minimum_required(VERSION 3.1.0)


# define your project name. This will be available through "${PROJECT_NAME}" now
project(DocGen)

find_package( OpenCV REQUIRED )
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON) 
# Instruct CMake to run moc, uic and rcc automatically when needed.
# This will intelegently 
set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTOUIC ON) 
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library (Qt5Widgets also finds the Qt5Core and Qt5Gui packages) 
find_package(Qt5Core REQUIRED) 
find_package(Qt5Widgets REQUIRED) 
find_package(Qt5Gui REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Test REQUIRED)

# Executables fail to build with Qt 5 in the default configuration, becasue the -fPIE flag is needed. This adds it. 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
 INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/QtAwesome/QtAwesome)

# Set up compilers (Clang, MSVC, GCC) so that C++11 can be used. The optimization settings are optional. Make sure not to "strip" the executable (-s in linker options for Clang and GCC) if you want to debug your application! Else debug information won't be available.
if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") 
    #set up compiler flags for Clang 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2") #support C++11 for std::, optimize
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O2") #optimize 
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU") 
    #check for G++ 5.4+ 
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE G++_VERSION) 
    if (G++_VERSION VERSION_LESS 5.4) 
            message(SEND_ERROR "You need at least G++ 5.4 to compile ${PROJECT_NAME}!") 
    endif() 
    #set up compiler flags for GCC 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2") #support C++11 for std::, optimize
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O2") #optimize 
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC") 
    set(CMAKE_DEBUG_POSTFIX "d") 
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE) 
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE) 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP") #multi-processor compilation 
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP") #multi-processor compilation 
endif()

# Now define your header files, .ui files here:
set(MYPROJECT_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/labelproject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imagelabel.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/boundingbox.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kittiexporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/darknetexporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exportdialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/multitracker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/baseexporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/baseimporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cocoexporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/darknetimporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gcpexporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imagedisplay.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/importdialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pascalvocexporter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/detection/detectoropencv.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/detection/detectorsetupdialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/refinerangedialog.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cocoimporter.h

    ${CMAKE_CURRENT_SOURCE_DIR}/src/importdialog.ui 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.ui 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exportdialog.ui 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imagedisplay.ui 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/detection/detectorsetupdialog.ui 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/refinerangedialog.ui

   ${CMAKE_CURRENT_SOURCE_DIR}/QtAwesome/QtAwesome/QtAwesome.h
   ${CMAKE_CURRENT_SOURCE_DIR}/QtAwesome/QtAwesome/QtAwesomeAnim.h

)

# Your source and .qrc files go here:
set(MYPROJECT_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/labelproject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imagelabel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kittiexporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/darknetexporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/exportdialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/multitracker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/baseexporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/baseimporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cocoexporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/darknetimporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gcpexporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imagedisplay.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/importdialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pascalvocexporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/detection/detectoropencv.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/detection/detectorsetupdialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/refinerangedialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cocoimporter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/qdarkstyle/style.qrc 

   ${CMAKE_CURRENT_SOURCE_DIR}/QtAwesome/QtAwesome/QtAwesome.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/QtAwesome/QtAwesome/QtAwesomeAnim.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/QtAwesome/QtAwesome/QtAwesome.qrc    
)

# Optional: You can also add OS-specific header or source files:
if(WIN32) 
    #LIST(APPEND MYPROJECT_SOURCES 
    #    ${CMAKE_CURRENT_SOURCE_DIR}/src/stuff_win.cpp 
    #) 
elseif(UNIX AND NOT APPLE) 
    #LIST(APPEND MYPROJECT_SOURCES 
    #    ${CMAKE_CURRENT_SOURCE_DIR}/src/stuff_linux.cpp 
    #) 
endif()

# Optional: Or OS-specific libraries:
if(WIN32) 
    #set(MYPROJECT_LIBRARIES 
    #    winmm 
    #) 
elseif(UNIX AND NOT APPLE) 
    #set(MYPROJECT_LIBRARIES 
    #    pthread 
    #) 
endif()

# Set up your build directory
set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR ${dir} CACHE PATH "Build directory" FORCE)  
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE) 
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)

# Set up your project build using include and source dirs and link libraries 
include_directories(${Qt5Widgets_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/proj ${CMAKE_CURRENT_SOURCE_DIR}/src) 
add_executable(${PROJECT_NAME} ${MYPROJECT_SOURCES} ${MYPROJECT_HEADERS}) 
target_link_libraries(${PROJECT_NAME}
                      ${OpenCV_LIBS}
                      ${Qt5Widgets_LIBRARIES}
                      ${Qt5Core_LIBRARIES}
                      ${Qt5Sql_LIBRARIES}
                      ${Qt5Gui_LIBRARIES}
                      ${Qt5Concurrent_LIBRARIES}
                      ${Qt5Test_LIBRARIES}
                      ${MYPROJECT_LIBRARIES})

set_target_properties( ${PROJECT_NAME} PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})