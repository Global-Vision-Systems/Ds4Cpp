cmake_minimum_required(VERSION 2.8)

project(${DS4CPP_BRIDGE_NAME})


# The version number.

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_VERSION 0)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})


#store binary outside platform specific place
SET(LIBRARY_OUTPUT_PATH ${BASE_WORK_DIRECTORY}/${OUTPUT_PROJECT_BINARIES_DIRECTORY})


#find Core and cppmicroservices lib to link with

if(BASE_WORK_DIRECTORY)
	#include Core 
	include_directories ("${BASE_WORK_DIRECTORY}/${DS4CPP_CORE_NAME}/service/")
	include_directories ("${BASE_WORK_DIRECTORY}/${DS4CPP_CORE_NAME}/include/")
	link_directories(${BASE_WORK_DIRECTORY}/${OUTPUT_PROJECT_BINARIES_DIRECTORY}/${BUILD_TYPE})
else()
	message("${DS4CPP_BRIDGE_NAME} Project error : use the parent directory as cmake root. Missing BASE_WORK_DIRECTORY.")
endif()

if(CPP_MICRO_SERVICES_DIRECTORY)
	#include CppMicroServices
	include_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/include")
	link_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/lib/${BUILD_TYPE}")
else()
	message("${DS4CPP_BRIDGE_NAME} Project error : use the parent directory as cmake root. Missing CPP_MICRO_SERVICES_DIRECTORY.")
endif()

 

#includes
include_directories("${PROJECT_BINARY_DIR}")

# We create a shared library
add_library(${PROJECT_NAME} SHARED src/components/ComponentDescriptorBridge_wrapper.cpp src/ComponentDescriptorBridgeModule.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_link_libraries (
	${PROJECT_NAME}
	debug ${DS4CPP_CORE_NAME}${CMAKE_DEBUG_POSTFIX}		optimized ${DS4CPP_CORE_NAME}
	debug ${CPP_MICRO_SERVICES_NAME}					optimized ${CPP_MICRO_SERVICES_NAME} 
)

#manage dependencies
add_dependencies(${DS4CPP_CORE_NAME} ${DS4CPP_CORE_NAME})


#call macro
USE_CPP11()

#call macro
Add_US_CXX_Flags()

  