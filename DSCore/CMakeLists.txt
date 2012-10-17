cmake_minimum_required(VERSION 2.8)

project(${DS4CPP_CORE_NAME})

# The version number.

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_VERSION 0)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})

#store binary outside platform specific place
SET(LIBRARY_OUTPUT_PATH ${BASE_WORK_DIRECTORY}/${OUTPUT_PROJECT_BINARIES_DIRECTORY})

# includes root directory
include_directories("${PROJECT_BINARY_DIR}")

# specific action if CPP_MICRO_SERVICES_DIRECTORY has been set
if(CPP_MICRO_SERVICES_DIRECTORY)
	#include CppMicroServices
	include_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/include")
	link_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/lib/${BUILD_TYPE}")
else()
	message("${DS4CPP_CORE_NAME} Project error : use the parent directory as cmake root. Missing CPP_MICRO_SERVICES_DIRECTORY.")
endif()
 
# get source and include files
FILE(GLOB CORE_SRCS src/*.cpp)
FILE(GLOB CORE_HEADERS include/*.h)

# group them in Folders  
SOURCE_GROUP("src" FILES ${CORE_SRCS})
SOURCE_GROUP("include" FILES ${CORE_HEADERS})
 
add_library(${PROJECT_NAME} SHARED ${CORE_SRCS} ${CORE_HEADERS} )
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

# add the library
target_link_libraries (
	${PROJECT_NAME} 	
	debug ${CPP_MICRO_SERVICES_NAME}	optimized ${CPP_MICRO_SERVICES_NAME} 
)

#call macro
USE_CPP11()

#call macro
Add_US_CXX_Flags()

  