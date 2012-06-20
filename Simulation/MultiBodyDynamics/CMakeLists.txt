set(source
	./MultiBodyDynamics/Joint.h
	./MultiBodyDynamics/BallJoint.h
	./MultiBodyDynamics/BallJoint.cpp 
	./MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.h
	./MultiBodyDynamics/ImpulseBasedDynamicsAlgorithm.cpp
)

set(simulationSource ${simulationSource} ${source}  )
source_group("simulation\\multibodydynamics" FILES ${source})