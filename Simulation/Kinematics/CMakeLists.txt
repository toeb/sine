SET(source
./Kinematics/KinematicBody.h
./Kinematics/KinematicBody.cpp
./Kinematics/CoordinateSystem.h
./Kinematics/CoordinateSystem.cpp
)

source_group("simulation\\kinematics" FILES ${source})
set(simulationSource ${simulationSource} ${source})