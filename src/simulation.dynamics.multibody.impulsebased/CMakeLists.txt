set(source
	./Joint.h	
	./ImpulseBasedMultiBodyModule.h
	./ImpulseBasedMultiBodyModule.cpp
)
source_group("" FILES ${source})

set(jointsSource
	./joints/BallJoint.h
	./joints/BallJoint.cpp 
	./joints/TranslationalJoint.h
	./joints/TranslationalJoint.cpp
	./joints/DirectionalJoint.h
	./joints/DirectionalJoint.cpp
	./joints/BallJoint.h
	./joints/BallJoint.cpp   
	./joints/DoubleRotationJoint.h
	./joints/DoubleRotationJoint.cpp 
)
source_group("joints" FILES ${jointsSource})
set(source ${source} ${jointsSource})

add_library(simulation.dynamics.multibody.impulsebased ${source})
target_link_libraries(simulation.dynamics.multibody.impulsebased  simulation.dynamics)
