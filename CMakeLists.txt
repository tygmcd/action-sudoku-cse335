# Declare the minimum required CMake version
cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)

# Name the project
project(ActionSudoku)
set(APPLICATION_LIBRARY GameLib)


# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system, since
# it doesn't seem to work. The CMake version works much better.
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file to initialize various settings
include(${wxWidgets_USE_FILE})

add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# This sets the Mac icon for the program
set(MACOSX_BUNDLE_ICON_FILE ActionSudoku.icns)
set_source_files_properties(ActionSudoku.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Define a variable containing a list of source files for the project
set(SOURCE_FILES main.cpp GameApp.cpp GameApp.h pch.h ActionSudoku.rc ActionSudoku.icns)

# Define the build target for the executable
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

add_subdirectory(Tests)

# Copy images into output directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)


if(APPLE)
    # When building for MacOS, also copy files into the bundle resources
    set(RESOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/ActionSudoku.app/Contents/Resources)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/ DESTINATION ${RESOURCE_DIR}/images/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/ DESTINATION ${RESOURCE_DIR}/levels/)

endif()

