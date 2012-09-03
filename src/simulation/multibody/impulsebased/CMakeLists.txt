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
set(source ${jointsSource})

add_library(multibody ${source})
project_folder("simulation/modules" multibody)
