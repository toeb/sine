


set(integrationSource 
 ./Integrator.h
 ./Integrator.cpp
 ./StepIntegrator.h
 ./StepIntegrator.cpp
 ./ISystemFunction.h 
 ./Evaluator.h
 ./Evaluator.cpp
 ./CompositeSystemFunction.h
 ./CompositeSystemFunction.cpp
 ./IntegratingSystem.h
 ./IntegratingSystem.cpp 
)
source_group("" FILES ${integrationSource})
set(implementationSource
./implementations/AdamsBashford4.h
./implementations/AdamsMoulton4.h
./implementations/ExplicitEuler.h
./implementations/SemiImplicitEuler.h
./implementations/ImplicitEuler.h
./implementations/RungeKutta2.h
./implementations/RungeKutta4.h
./implementations/RungeKuttaFehlberg45.h
./implementations/Trapezoidal.h
./implementations/AdamsBashford4.cpp
./implementations/AdamsMoulton4.cpp
./implementations/ExplicitEuler.cpp
./implementations/SemiImplicitEuler.cpp
./implementations/ImplicitEuler.cpp
./implementations/RungeKutta2.cpp
./implementations/RungeKutta4.cpp
./implementations/RungeKuttaFehlberg45.cpp
./implementations/Trapezoidal.cpp
 )
source_group("implementation" FILES ${implementationSource})
 
 
add_library(simulation.integration ${integrationSource} ${implementationSource} )
target_link_libraries(simulation.integration  simulation simulation.state math)