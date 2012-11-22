cmake_minimum_required(VERSION 2.8)

project(${DS4CPP_DEMO_NAME})

# The version number.

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_VERSION 0)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})


#store binary outside platform specific place
SET(LIBRARY_OUTPUT_PATH ${BASE_WORK_DIRECTORY}/${OUTPUT_PROJECT_BINARIES_DIRECTORY})


#find Core and CppMicroServices and ComponentDescriptorBridge to link with
if(BASE_WORK_DIRECTORY AND BUILD_TYPE_OUTPUT_DIR)
	#include Core and ComponentDescriptorBridge
	include_directories ("${BASE_WORK_DIRECTORY}/${DS4CPP_CORE_NAME}/services/")
	include_directories ("${BASE_WORK_DIRECTORY}/${DS4CPP_CORE_NAME}/include/")
	include_directories ("${BASE_WORK_DIRECTORY}/${DS4CPP_BRIDGE_NAME}/include")
	link_directories(${BASE_WORK_DIRECTORY}/${OUTPUT_PROJECT_BINARIES_DIRECTORY}/${BUILD_TYPE})
endif()

if(CPP_MICRO_SERVICES_DIRECTORY)
	#include CppMicroServices
	include_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/include")
	link_directories ("${CPP_MICRO_SERVICES_DIRECTORY}/lib/${BUILD_TYPE}")
endif()

  
 
 # get source and include files
FILE(GLOB COMPONENTS_SRCS components/*.cpp)

#Console Greeter
FILE(GLOB COMPONENTS_CONSOLE_GREETER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.ConsoleGreeter/src/*.cpp)
FILE(GLOB COMPONENTS_CONSOLE_GREETER_SRCS_GEN ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.ConsoleGreeter/src-gen/*.cpp)
FILE(GLOB COMPONENTS_CONSOLE_GREETER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.ConsoleGreeter/include/*.hpp)

#English Provider
FILE(GLOB COMPONENTS_ENGLISH_PROVIDER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.EnglishGreetProvider/src/*.cpp)
FILE(GLOB COMPONENTS_ENGLISH_PROVIDER_SRCS_GEN ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.EnglishGreetProvider/src-gen/*.cpp)
FILE(GLOB COMPONENTS_ENGLISH_PROVIDER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.EnglishGreetProvider/include/*.hpp)

#French Provider
FILE(GLOB COMPONENTS_FRENCH_PROVIDER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.FrenchGreetProvider/src/*.cpp)
FILE(GLOB COMPONENTS_FRENCH_PROVIDER_SRCS_GEN ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.FrenchGreetProvider/src-gen/*.cpp)
FILE(GLOB COMPONENTS_FRENCH_PROVIDER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.FrenchGreetProvider/include/*.hpp)

#Greet Manager
FILE(GLOB COMPONENTS_GREET_MANAGER_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.GreetManagerImpl/src/*.cpp)
FILE(GLOB COMPONENTS_GREET_MANAGER_SRCS_GEN ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.GreetManagerImpl/src-gen/*.cpp)
FILE(GLOB COMPONENTS_GREET_MANAGER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/components/greetdemo.GreetManagerImpl/include/*.hpp)

# services
FILE(GLOB SERVICES_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/services/*.cpp)
FILE(GLOB SERVICES_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/services/*.hpp)

# group them in Folders  
SOURCE_GROUP("components" FILES ${COMPONENTS_SRCS})

#console greeter
SOURCE_GROUP("components\\greetdemo.ConsoleGreeter\\src" FILES ${COMPONENTS_CONSOLE_GREETER_SRCS})
SOURCE_GROUP("components\\greetdemo.ConsoleGreeter\\src-gen" FILES ${COMPONENTS_CONSOLE_GREETER_SRCS_GEN})
SOURCE_GROUP("components\\greetdemo.ConsoleGreeter\\include" FILES ${COMPONENTS_CONSOLE_GREETER_HEADERS})

#English Provider
SOURCE_GROUP("components\\greetdemo.EnglishGreetProvider\\src" FILES ${COMPONENTS_ENGLISH_PROVIDER_SRCS})
SOURCE_GROUP("components\\greetdemo.EnglishGreetProvider\\src-gen" FILES ${COMPONENTS_ENGLISH_PROVIDER_SRCS_GEN})
SOURCE_GROUP("components\\greetdemo.EnglishGreetProvider\\include" FILES ${COMPONENTS_ENGLISH_PROVIDER_HEADERS})

#French Provider
SOURCE_GROUP("components\\greetdemo.FrenchGreetProvider\\src" FILES ${COMPONENTS_FRENCH_PROVIDER_SRCS})
SOURCE_GROUP("components\\greetdemo.FrenchGreetProvider\\src-gen" FILES ${COMPONENTS_FRENCH_PROVIDER_SRCS_GEN})
SOURCE_GROUP("components\\greetdemo.FrenchGreetProvider\\include" FILES ${COMPONENTS_FRENCH_PROVIDER_HEADERS})

#Greet Manager
SOURCE_GROUP("components\\greetdemo.GreetManagerImpl\\src" FILES ${COMPONENTS_GREET_MANAGER_SRCS})
SOURCE_GROUP("components\\greetdemo.GreetManagerImpl\\src-gen" FILES ${COMPONENTS_GREET_MANAGER_SRCS_GEN})
SOURCE_GROUP("components\\greetdemo.GreetManagerImpl\\include" FILES ${COMPONENTS_GREET_MANAGER_HEADERS})


#group services
SOURCE_GROUP("services" FILES ${SERVICES_SRCS})
SOURCE_GROUP("services" FILES ${SERVICES_HEADERS})


#includes
include_directories("${PROJECT_BINARY_DIR}")
# includes
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/components")
#includes
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/services")


# We create a shared library
add_library(${PROJECT_NAME} MODULE 
	${COMPONENTS_SRCS}
	${COMPONENTS_CONSOLE_GREETER_SRCS}	${COMPONENTS_CONSOLE_GREETER_SRCS_GEN}	${COMPONENTS_CONSOLE_GREETER_HEADERS}
	${COMPONENTS_ENGLISH_PROVIDER_SRCS} ${COMPONENTS_ENGLISH_PROVIDER_SRCS_GEN} ${COMPONENTS_ENGLISH_PROVIDER_HEADERS}
	${COMPONENTS_FRENCH_PROVIDER_SRCS} 	${COMPONENTS_FRENCH_PROVIDER_SRCS_GEN} 	${COMPONENTS_FRENCH_PROVIDER_HEADERS}
	${COMPONENTS_GREET_MANAGER_SRCS} 	${COMPONENTS_GREET_MANAGER_SRCS_GEN} 	${COMPONENTS_GREET_MANAGER_HEADERS}
	${SERVICES_SRCS} 					${SERVICES_HEADERS}
)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")


target_link_libraries (
${PROJECT_NAME} 
debug ${DS4CPP_CORE_NAME}${CMAKE_DEBUG_POSTFIX}		optimized ${DS4CPP_CORE_NAME}
debug ${DS4CPP_BRIDGE_NAME}${CMAKE_DEBUG_POSTFIX}	optimized ${DS4CPP_BRIDGE_NAME}
debug ${CPP_MICRO_SERVICES_NAME}					optimized ${CPP_MICRO_SERVICES_NAME} 
)



#manage dependencies
add_dependencies(${DS4CPP_DEMO_NAME} ${DS4CPP_CORE_NAME})
add_dependencies(${DS4CPP_DEMO_NAME} ${DS4CPP_BRIDGE_NAME})


#call macro
USE_CPP11()

#call macro
Add_US_CXX_Flags()

  
