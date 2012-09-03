set(source
	./Joint.h	
	./ImpulseBasedMultiBodyModule.h
	./ImpulseBasedMultiBodyModule.cpp
)
source_group("" FILES ${source})

set(jointsSource
	./joints/BallJoint.h
	./joints/BallJoint.cpp 
)
source_group("joints" FILES ${jointsSource})
set(source ${jointsSource})

add_library(multibody ${source})
project_folder("simulation/modules" multibody)
