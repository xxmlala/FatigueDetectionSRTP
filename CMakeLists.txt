cmake_minimum_required(VERSION 2.8)
project( FatigueDetection )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( face fatigueDetection.cpp  )
target_link_libraries( face ${OpenCV_LIBS} )

