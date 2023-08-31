# #################################################################################################
# BIGIA SYSTEM COMPILE
# #################################################################################################
cmake_minimum_required(VERSION 3.9)
project(OpenCV_POCs)

set(THREAD_LIBS "-lpthread")

# #################################################################################################
# Show libs dirs
# #################################################################################################

# Includes
include_directories( SYSTEM ${OpenCV_INCLUDE_DIRS} )
include_directories( SYSTEM ${CMAKE_PREFIX_PATH}/include )
include_directories( SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/include )

# #################################################################################################
# OpenCV - Library
# #################################################################################################
find_package( OpenCV REQUIRED )
#message("OpenCV_LIBS: " ${OpenCV_LIBS} )

# #################################################################################################
# CAPTOR Build if enabled
# #################################################################################################
add_executable(Camera Camera.cpp)
target_link_libraries(Camera ${THREAD_LIBS} ${OpenCV_LIBS} )

