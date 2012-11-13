cmake_minimum_required(VERSION 2.8)

#set the configuration type to debug and release only (Debug;Release;MinSizeRel;RelWithDebInfo)
#always do it before project command
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

#declare project
project(DS4Cpp)

# The version number.

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_VERSION 0)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})

#output directory where to put the libraries
set(OUTPUT_PROJECT_BINARIES_DIRECTORY "bin")

#use constants for names
set(DS4CPP_CORE_NAME "DSCore")
set(DS4CPP_BRIDGE_NAME "DSBridge")
set(DS4CPP_LAUNCHER_NAME "DSLauncher")
set(DS4CPP_DEMO_NAME "DSDemo")
set(DS4CPP_FACTORY_DEMO_NAME "DSFactoryDemo")
set(CPP_MICRO_SERVICES_NAME "CppMicroServices") 

#set default value for DS4CPP directory. If not valid, ask for it
set(DEFAULT_BASE_WORK_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
IF(NOT EXISTS ${DEFAULT_BASE_WORK_DIRECTORY})
	set(BASE_WORK_DIRECTORY "" CACHE PATH "DS4Cpp root path")
ELSE()
	set(BASE_WORK_DIRECTORY ${DEFAULT_BASE_WORK_DIRECTORY})
ENDIF()

#set default value for CPP Microservice directory. If not valid, ask for it
set(DEFAULT_CPP_MICRO_SERVICES_DIRECTORY "./CppMicroServices/binaries/")
IF( NOT EXISTS ${DEFAULT_CPP_MICRO_SERVICES_DIRECTORY})
	set(CPP_MICRO_SERVICES_DIRECTORY "" CACHE PATH "CppMicroServices build path (where to find lib, bin and include)")
ELSE()
	set(CPP_MICRO_SERVICES_DIRECTORY ${DEFAULT_CPP_MICRO_SERVICES_DIRECTORY})
ENDIF()

#Add a "d" on debug output
SET(CMAKE_DEBUG_POSTFIX "d")

#variable for other projects
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(BUILD_TYPE_OUTPUT_DIR "Debug")
ELSE()
	set(BUILD_TYPE_OUTPUT_DIR "Release")
#	set(BUILD_NAME_POSTFIX "")
ENDIF()


#-----------------------------------------------------------------------------
# CMake options
#-----------------------------------------------------------------------------


#define macro before including other projects
macro (USE_CPP11)
    set(US_USE_C++11 1)
endmacro()


macro (Add_US_CXX_Flags)
	#-----------------------------------------------------------------------------
	# US C/CXX Flags
	#-----------------------------------------------------------------------------

	set(US_C_FLAGS "${COVERAGE_C_FLAGS} ${ADDITIONAL_C_FLAGS}")
	set(US_CXX_FLAGS "${COVERAGE_CXX_FLAGS} ${ADDITIONAL_CXX_FLAGS}")

	# This is used as a preprocessor define
	if(US_USE_C++11)
    	if(CMAKE_COMPILER_IS_GNUCXX)
	      set(CMAKE_CXX_FLAGS " -fdiagnostics-show-option -std=c++0x -Woverloaded-virtual -Wstrict-null-sentinel -Wsign-promo  -Wextra -Wpointer-arith -Winvalid-pch -Wcast-align -Wwrite-strings -D_FORTIFY_SOURCE=2")
	    endif()
	endif()
endmacro()



#add core
add_subdirectory("${BASE_WORK_DIRECTORY}/${DS4CPP_CORE_NAME}")

#add component-descriptor-bridge
add_subdirectory("${BASE_WORK_DIRECTORY}/${DS4CPP_BRIDGE_NAME}")


#add demo (if required by user)
OPTION(USE_GREET_DEMO "Add greet demo project")
IF( USE_GREET_DEMO )
	add_subdirectory("${BASE_WORK_DIRECTORY}/${DS4CPP_DEMO_NAME}")
	add_subdirectory("${BASE_WORK_DIRECTORY}/${DS4CPP_FACTORY_DEMO_NAME}")
ENDIF()

#add launcher (if required by user)
OPTION(USE_SIMPLE_LAUNCHER "Add simple launcher project")
IF( USE_SIMPLE_LAUNCHER )
	add_subdirectory("${BASE_WORK_DIRECTORY}/${DS4CPP_LAUNCHER_NAME}")
ENDIF()


