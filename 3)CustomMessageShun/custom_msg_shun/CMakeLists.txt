cmake_minimum_required(VERSION 3.0.2)
project(custom_msg_shun)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  dog_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES custom_msg_shun
#  CATKIN_DEPENDS roscpp std_msgs dog_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(talkerOne src/talkerOne.cpp)
target_link_libraries(talkerOne ${catkin_LIBRARIES})
add_dependencies(talkerOne ${catkin_EXPORTED_TARGETS})

add_executable(talkerTwo src/talkerTwo.cpp)
target_link_libraries(talkerTwo ${catkin_LIBRARIES})
add_dependencies(talkerTwo ${catkin_EXPORTED_TARGETS})

add_executable(breeder src/test.cpp)
target_link_libraries(breeder ${catkin_LIBRARIES})
add_dependencies(breeder ${catkin_EXPORTED_TARGETS})

add_executable(finalListener src/finalListener.cpp)
target_link_libraries(finalListener ${catkin_LIBRARIES})
add_dependencies(finalListener  ${catkin_EXPORTED_TARGETS})
~
~ 
