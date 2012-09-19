SET (source
	./DynamicBodyModule.h
	./DynamicBodyModule.cpp
	./Particle.cpp
	./Particle.h   
	./RigidBody.h
	./RigidBody.cpp
	./DynamicBody.h
	./DynamicBody.cpp
)

source_group("src" FILES ${source})
set(connectionSource
	
	./connection/ParticleConnector.h
	./connection/ParticleConnector.cpp
	./connection/RigidBodyConnector.h
	./connection/RigidBodyConnector.cpp
	./connection/Connector.h
	./connection/Connector.cpp
	./connection/ConnectorModule.h
	./connection/ConnectorModule.cpp
	./connection/ConnectorFactory.h
	./connection/ConnectorFactory.cpp

)
source_group("src\\connection" FILES ${connectionSource})
set (bodyprimitivesSource
	./primitives/DynamicBox.h
	./primitives/DynamicBox.cpp
	./primitives/DynamicSphere.h
	./primitives/DynamicSphere.cpp
	./primitives/DynamicGeometry.h
	./primitives/DynamicGeometry.cpp
)
source_group("src\\bodyprimitives" FILES ${bodyprimitivesSource})

add_library(dynamics ${source} ${connectionSource} ${bodyprimitivesSource})
project_folder("simulation/modules" dynamics)
target_link_libraries(dynamics common kinematics core)

