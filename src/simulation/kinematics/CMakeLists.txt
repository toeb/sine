SET(source
./KinematicBody.h
./KinematicBody.cpp
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
add_library(kinematics ${source} CMakeLists.txt)
project_folder("simulation/modules" kinematics)
target_link_libraries(kinematics core math)