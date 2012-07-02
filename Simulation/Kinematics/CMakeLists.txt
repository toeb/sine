SET(source
./Kinematics/KinematicBody.h
./Kinematics/KinematicBody.cpp
./Kinematics/CoordinateSystem.h
./Kinematics/CoordinateSystem.cpp
./Kinematics/Position.h
./Kinematics/Orientation.h
./Kinematics/Velocity.h
./Kinematics/AngularVelocity.h
./Kinematics/Acceleration.h
./Kinematics/AngularAcceleration.h
)

source_group("simulation\\kinematics" FILES ${source})
set(simulationSource ${simulationSource} ${source})