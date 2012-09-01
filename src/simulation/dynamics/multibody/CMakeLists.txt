set(source
	./impulseBased/Joint.h
	./impulseBased/BallJoint.h
	./impulseBased/BallJoint.cpp 
	./impulseBased/ImpulseBasedDynamicsAlgorithm.h
	./impulseBased/ImpulseBasedDynamicsAlgorithm.cpp
)

set(simulationSource ${simulationSource} ${source}  )
source_group("simulation\\multibodydynamics\\impulsebased" FILES ${source})