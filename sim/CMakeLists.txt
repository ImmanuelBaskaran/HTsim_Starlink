cmake_minimum_required(VERSION 3.13)
project(sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -g -fpermissive -Wuninitialized")

include_directories(.)
include_directories(Starlink)


add_custom_target(buildHTSim COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )



add_executable(sim
        Starlink/simple.cpp
        Starlink/ConnectionMatrix.cpp
        Starlink/LaserLink.cpp
        Starlink/GroundStation.cpp
        Starlink/Satellite.cpp
        Starlink/OrbitalPlane.cpp
        Starlink/RouteFinder.cpp Starlink/RouteFinder.h Starlink/Constellation.cpp Starlink/Constellation.h)

target_link_libraries(sim ${CMAKE_CURRENT_SOURCE_DIR}/libhtsim.a)
add_dependencies(sim buildHTSim)