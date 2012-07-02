
SET(visualisation_SRC
./MiniGL.h
./MiniGL.cpp
./IRenderer.h
./RenderEngine.h
./RenderEngine.cpp
./CompositeRenderer.h
./CompositeRenderer.cpp
./RenderManager.h
./RenderManager.cpp
./InputHandler.h
./InputHandler.cpp
./Camera.h
)	
SET(renderers_SRC
./Renderers/SimulationRunnerRenderer.h
./Renderers/SimulationRunnerRenderer.cpp
./Renderers/PolygonRenderer.h
./Renderers/PolygonRenderer.cpp
./Renderers/LightRenderer.h
./Renderers/LightRenderer.cpp
./Renderers/CameraRenderer.h
./Renderers/CameraRenderer.cpp
./Renderers/CoordinateSystemRenderer.h
./Renderers/CoordinateSystemRenderer.cpp
./Renderers/TextRenderer.h
./Renderers/TextRenderer.cpp
./Renderers/ConnectorRenderer.h
./Renderers/ConnectorRenderer.cpp
./Renderers/ConnectorVelocityRenderer.h
./Renderers/ConnectorVelocityRenderer.cpp
./Renderers/ConnectorForceRenderer.h
./Renderers/ConnectorForceRenderer.cpp
./Renderers/ParticleRenderer.h
./Renderers/ParticleRenderer.cpp
./Renderers/BoxRenderer.h
./Renderers/BoxRenderer.cpp
./Renderers/PointRenderer.h
./Renderers/PointRenderer.cpp
./Renderers/SphereRenderer.h
./Renderers/SphereRenderer.cpp	
./Renderers/SpringRenderer.h
./Renderers/SpringRenderer.cpp	
./Renderers/CollisionRenderer.h
./Renderers/CollisionRenderer.cpp	
./Renderers/OctreeRenderer.h
./Renderers/OctreeRenderer.cpp	
./Renderers/PlaneRenderer.h
./Renderers/PlaneRenderer.cpp	
)

set(tweakbar_SRC
./Renderers/TweakBar/TweakBarRenderer.cpp
./Renderers/TweakBar/TweakBarRenderer.h
)

set(userinterface_SRC
./UserInterface/DelegateAction.h
./UserInterface/DelegateAction.cpp
./UserInterface/IValue.h
./UserInterface/IValue.cpp
./UserInterface/IAction.h
./UserInterface/IAction.cpp
./UserInterface/RealValue.h
./UserInterface/RealValue.cpp
./UserInterface/Vector3DValue.h
./UserInterface/Vector3DValue.cpp

)

set(mesh_SRC
./Renderers/Mesh/MeshRenderer.h
./Renderers/Mesh/MeshRenderer.cpp
)
source_group("visualization\\renderers\\mesh" FILES ${mesh_SRC})

add_library(Visualization 
${visualisation_SRC}         
${renderers_SRC}
${tweakbar_SRC}
${userinterface_SRC}
${mesh_SRC})

source_group("visualization" FILES ${visualisation_SRC})
source_group("visualization\\renderers\\tweakbar" FILES ${tweakbar_SRC})
source_group("visualization\\renderers" FILES ${renderers_SRC})
source_group("visualization\\userinterface" FILES ${userinterface_SRC})