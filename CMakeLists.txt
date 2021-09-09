cmake_minimum_required(VERSION 3.0.2)
project(eigen_json_io)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED)


find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories( ${EIGEN3_INCLUDE_DIRS} )



catkin_package()


include_directories( include )

######## TEST #########
add_executable( test_1 test/1.cc )
target_link_libraries( test_1 ${catkin_LIBRARIES} )

add_executable( test_2 test/2.cc )
target_link_libraries( test_2 ${catkin_LIBRARIES} )
#######################
