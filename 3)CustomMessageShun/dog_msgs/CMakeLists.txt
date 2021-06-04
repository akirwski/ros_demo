cmake_minimum_required(VERSION 3.0.2)
project(dog_msgs)

## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  std_msgs
  message_generation
)


#Generate messages in the 'msg' folder
add_message_files(
   FILES
   dogMsg.msg
 )


## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
)

## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES dog_msgs
#  CATKIN_DEPENDS std_msgs
#  DEPENDS system_lib
   CATKIN_DEPENDS message_runtime
)

## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
