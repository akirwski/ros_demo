add_executable(talkerOne src/talkerOne.cpp)
target_link_libraries(talkerOne ${catkin_LIBRARIES})

add_executable(talkerTwo src/talkerTwo.cpp)
target_link_libraries(talkerTwo ${catkin_LIBRARIES})

add_executable(listener src/ListenerClass.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})

add_executable(finalListener src/finalListener.cpp)
target_link_libraries(finalListener ${catkin_LIBRARIES})
