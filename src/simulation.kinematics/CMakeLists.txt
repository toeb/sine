SET(source
./KinematicCoordinates.h
./KinematicCoordinates.cpp
./KinematicPoint.h
./KinematicPoint.cpp
./CoordinateSystem.h
./CoordinateSystem.cpp
./Position.h
./Orientation.h
./Velocity.h
./AngularVelocity.h
./Acceleration.h
./AngularAcceleration.h
)

source_group("src" FILES ${source})
add_library(simulation.kinematics ${source} CMakeLists.txt)
target_link_libraries(simulation.kinematics simulation math)