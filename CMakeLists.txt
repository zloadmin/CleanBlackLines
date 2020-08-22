cmake_minimum_required(VERSION 2.8)
project( CleanBlackLines )
find_package( OpenCV REQUIRED )
add_executable( CleanBlackLines CleanBlackLines.cpp )
target_link_libraries( CleanBlackLines ${OpenCV_LIBS} )


if (UNIX)
    target_link_libraries(CleanBlackLines stdc++fs)
endif (UNIX)
