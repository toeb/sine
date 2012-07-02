SET (source
	./Dynamics/DynamicBodyModule.h
	./Dynamics/DynamicBodyModule.cpp
	./Dynamics/Particle.cpp
	./Dynamics/Particle.h   
	./Dynamics/RigidBody.h
	./Dynamics/RigidBody.cpp
	./Dynamics/DynamicBody.h
	./Dynamics/DynamicBody.cpp
)

source_group("simulation\\dynamics" FILES ${source})
set(connectionSource
	
	./Dynamics/Connection/ParticleConnector.h
	./Dynamics/Connection/ParticleConnector.cpp
	./Dynamics/Connection/RigidBodyConnector.h
	./Dynamics/Connection/RigidBodyConnector.cpp
	./Dynamics/Connection/Connector.h
	./Dynamics/Connection/Connector.cpp
	./Dynamics/Connection/ConnectorModule.h
	./Dynamics/Connection/ConnectorModule.cpp
	./Dynamics/Connection/ConnectorFactory.h
	./Dynamics/Connection/ConnectorFactory.cpp

)
source_group("simulation\\dynamics\\connection" FILES ${connectionSource})
set (bodyprimitives_SRC
	./Dynamics/BodyPrimitives/DynamicBox.h
	./Dynamics/BodyPrimitives/DynamicBox.cpp
	./Dynamics/BodyPrimitives/DynamicSphere.h
	./Dynamics/BodyPrimitives/DynamicSphere.cpp
	./Dynamics/BodyPrimitives/DynamicGeometry.h
	./Dynamics/BodyPrimitives/DynamicGeometry.cpp
)
source_group("simulation\\dynamics\\bodyprimitives" FILES ${bodyprimitives_SRC})

set(simulationSource ${simulationSource} ${source} ${bodyprimitives_SRC} ${connectionSource})

