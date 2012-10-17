cmake_minimum_required(VERSION 2.8)

project(${DS4CPP_LAUNCHER_NAME})

# The version number.

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_VERSION 0)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})

#set the output directory
SET(EXECUTABLE_OUTPUT_PATH ${BASE_WORK_DIRECTORY}/${OUTPUT_PROJECT_BINARIES_DIRECTORY})

# includes
include_directories("${PROJECT_BINARY_DIR}")

if(CPP_MICRO_SERVICES_DIRECTORY)
	#include CppMicroServices
	include_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/include")
	link_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/lib/${BUILD_TYPE}")
endif()

add_executable(${PROJECT_NAME} src/Launcher.cpp src/ModuleLoader.cpp)

target_link_libraries (${PROJECT_NAME} ${CPP_MICRO_SERVICES_NAME} )


#call macro
USE_CPP11()

#call macro
Add_US_CXX_Flags()

  