#
# The find_package macro for Orocos-RTT works best with
# cmake >= 2.6.3
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
 
#
# This creates a standard cmake project. You may extend this file with
# any cmake macro you see fit.
#
project(trajectoryService)

add_compile_options(-std=c++11)
 
# Set the CMAKE_PREFIX_PATH in case you're not using Orocos through ROS
# for helping these find commands find RTT.
find_package(OROCOS-RTT REQUIRED ${RTT_HINTS})
 
# Defines the orocos_* cmake macros. See that file for additional
# documentation.
include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)

find_package(ignition-transport2 REQUIRED)
include_directories(${IGNITION-TRANSPORT_INCLUDE_DIRS})
#link_directories(${IGNITION-TRANSPORT_LIBRARY_DIRS})


 
#
# Components, types and plugins.
#
# The CMake 'target' names are identical to the first argument of the
# macros below, except for orocos_typegen_headers, where the target is fully
# controlled by generated code of 'typegen'.
#
 
 
# Creates a component library libexample-<target>.so
# and installs in the directory lib/orocos/example/
#
#orocos_component(orocosTrajectoryService orocosTrajectoryService.cpp) # ...you may add multiple source files
orocos_service(orocosTrajectoryService orocosTrajectoryService.cpp)
target_link_libraries(orocosTrajectoryService ${IGNITION-TRANSPORT_LIBRARIES})
# You may add multiple orocos_component statements.
 
#
# Building a typekit (recommended):
#
# Creates a typekit library libexample-types-<target>.so
# and installs in the directory lib/orocos/example/types/
#
#orocos_typegen_headers(example-types.hpp) # ...you may add multiple header files
#
# You may only have *ONE* orocos_typegen_headers statement !
 
#
# Building a normal library (optional):
#
# Creates a library libsupport-<target>.so and installs it in
# lib/
#
#orocos_library(support support.cpp) # ...you may add multiple source files
#
# You may add multiple orocos_library statements.
 
 
#
# Building a Plugin or Service (optional):
#
# Creates a plugin library libexample-service-<target>.so or libexample-plugin-<target>.so
# and installs in the directory lib/orocos/example/plugins/
#
# Be aware that a plugin may only have the loadRTTPlugin() function once defined in a .cpp file.
# This function is defined by the plugin and service CPP macros.
#
#orocos_service(example-service example-service.cpp) # ...only one service per library !
#orocos_plugin(example-plugin example-plugin.cpp) # ...only one plugin function per library !
#
# You may add multiple orocos_plugin/orocos_service statements.
 
 
#
# Additional headers (not in typekit):
#
# Installs in the include/orocos/example/ directory
#
#orocos_install_headers( ignition/msgs.hh ignition/transport.hh ) # ...you may add multiple header files

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
# You may add multiple orocos_install_headers statements.
 
#
# Generates and installs our package. Must be the last statement such
# that it can pick up all above settings.
#
orocos_generate_package()
