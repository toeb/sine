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
	
	./Dynamics/connection/ParticleConnector.h
	./Dynamics/connection/ParticleConnector.cpp
	./Dynamics/connection/RigidBodyConnector.h
	./Dynamics/connection/RigidBodyConnector.cpp
	./Dynamics/connection/Connector.h
	./Dynamics/connection/Connector.cpp
	./Dynamics/connection/ConnectorModule.h
	./Dynamics/connection/ConnectorModule.cpp
	./Dynamics/connection/ConnectorFactory.h
	./Dynamics/connection/ConnectorFactory.cpp

)
source_group("simulation\\dynamics\\connection" FILES ${connectionSource})
set (bodyprimitives_SRC
	./Dynamics/primitives/DynamicBox.h
	./Dynamics/primitives/DynamicBox.cpp
	./Dynamics/primitives/DynamicSphere.h
	./Dynamics/primitives/DynamicSphere.cpp
	./Dynamics/primitives/DynamicGeometry.h
	./Dynamics/primitives/DynamicGeometry.cpp
)
source_group("simulation\\dynamics\\bodyprimitives" FILES ${bodyprimitives_SRC})

set(simulationSource ${simulationSource} ${source} ${bodyprimitives_SRC} ${connectionSource})

