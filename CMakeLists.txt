cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(trajectoryService)
find_package(gazebo 8.0 REQUIRED)
if(GAZEBO_VERSION)
  if(${GAZEBO_VERSION} GREATER 6)
      add_definitions(-DGAZEBO_GREATER_6)
  endif()
endif()


find_package(ignition-transport2 REQUIRED)
include_directories(${IGNITION-TRANSPORT_INCLUDE_DIRS})
link_directories(${IGNITION-TRANSPORT_LIBRARY_DIRS})

message(STATUS "GAZEBO version: ${GAZEBO_VERSION}")
message(STATUS "GAZEBO_INCLUDE_DIRS: ${GAZEBO_INCLUDE_DIRS}")
message(STATUS "GAZEBO_LIBRARY_DIRS: ${GAZEBO_LIBRARY_DIRS}")
message(STATUS "GAZEBO_LIBRARIES: ${GAZEBO_LIBRARIES}")


include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(trajectory_wp SHARED src/gazebo/trajectory_wp.cc)
target_link_libraries(trajectory_wp ${GAZEBO_LIBRARIES} ${IGNITION-TRANSPORT_LIBRARIES})

add_executable(commander example/gazebo/commander.cc)
target_link_libraries(commander ${GAZEBO_LIBRARIES} ${IGNITION-TRANSPORT_LIBRARIES})


find_package(OROCOS-RTT ${RTT_HINTS})

add_compile_options(-std=c++11)
if(OROCOS-RTT_FOUND)
	include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)
	orocos_service(orocosTrajectoryService src/orocos/orocosTrajectoryService.cpp)
	target_link_libraries(orocosTrajectoryService ${IGNITION-TRANSPORT_LIBRARIES})
	orocos_generate_package()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
