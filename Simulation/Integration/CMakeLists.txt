
SET (integrators_SRC
  ./Integration/IIntegrable.h
  ./Integration/Integrator.h
  ./Integration/Integrator.cpp 
  ./Integration/ISystemFunction.h
  ./Integration/ISystemFunction.cpp
  ./Integration/SingleStepIntegrator.h
  ./Integration/SingleStepIntegrator.cpp
  ./Integration/CompositeIntegratable.h
  ./Integration/CompositeIntegratable.cpp)
  
source_group("simulation\\integration" FILES ${integrators_SRC})
set(simulationSource ${simulationSource} ${integrators_SRC})

SET (integratorImplementations_SRC
  ./Integration/Implementations/ExplicitEuler.h
  ./Integration/Implementations/ExplicitEuler.cpp
  ./Integration/Implementations/ImplicitEuler.h
  ./Integration/Implementations/ImplicitEuler.cpp
  ./Integration/Implementations/RungeKutta4.h
  ./Integration/Implementations/RungeKutta4.cpp
  ./Integration/Implementations/RungeKuttaFehlberg45.h
  ./Integration/Implementations/RungeKuttaFehlberg45.cpp)
  
 
source_group("simulation\\integration\\implementations" FILES ${integratorImplementations_SRC})
set(simulationSource ${simulationSource} ${integratorImplementations_SRC})

