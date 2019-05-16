cmake_minimum_required(VERSION 2.8.3)
project(motoman_sia5d_moveit_config)

find_package(catkin REQUIRED)

catkin_package()

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

#add_executable(panda1 src/panda1.cpp)
#target_link_libraries(panda1 ${catkin_LIBRARIES})

