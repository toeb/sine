SET (source
	./Dynamics/DynamicBodyModule.h
	./Dynamics/DynamicBodyModule.cpp
	./Dynamics/ConnectorModule.h
	./Dynamics/ConnectorModule.cpp
	./Dynamics/Particle.cpp
	./Dynamics/Particle.h   
	./Dynamics/RigidBody.h
	./Dynamics/RigidBody.cpp
	./Dynamics/Connector.h
	./Dynamics/Connector.cpp
	./Dynamics/ParticleConnector.h
	./Dynamics/ParticleConnector.cpp
	./Dynamics/RigidBodyConnector.h
	./Dynamics/RigidBodyConnector.cpp
	./Dynamics/DynamicBody.h
	./Dynamics/DynamicBody.cpp
)
source_group("simulation\\dynamics" FILES ${source})

set (bodyprimitives_SRC
	./Dynamics/BodyPrimitives/Box.h
	./Dynamics/BodyPrimitives/Box.cpp
	./Dynamics/BodyPrimitives/Sphere.h
	./Dynamics/BodyPrimitives/Sphere.cpp
)
source_group("simulation\\dynamics\\bodyprimitives" FILES ${bodyprimitives_SRC})

set(simulationSource ${simulationSource} ${source} ${bodyprimitives_SRC})

