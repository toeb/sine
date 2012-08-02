set(source
	./MultiBodyDynamics/ImpulseBased/Joint.h
	./MultiBodyDynamics/ImpulseBased/BallJoint.h
	./MultiBodyDynamics/ImpulseBased/BallJoint.cpp 
	./MultiBodyDynamics/ImpulseBased/ImpulseBasedDynamicsAlgorithm.h
	./MultiBodyDynamics/ImpulseBased/ImpulseBasedDynamicsAlgorithm.cpp
)

set(simulationSource ${simulationSource} ${source}  )
source_group("simulation\\multibodydynamics\\impulsebased" FILES ${source})