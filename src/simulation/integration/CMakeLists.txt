


set(integrationSource
 ./IStatefulObject.h
 ./Integrator.h
 ./Integrator.cpp
 ./State.h
 ./State.cpp
 ./StepIntegrator.h
 ./StepIntegrator.cpp
 ./ISystemFunction.h 
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
 
 set(moduleSource
 ./module/SystemModule.h
 ./module/SystemModule.cpp 
 )
source_group("module" FILES ${moduleSource})

 set(compositeSource
 ./composites/CompositeSystemFunction.h
 ./composites/CompositeSystemFunction.cpp
 ./composites/CompositeStatefulObject.h
 ./composites/CompositeStatefulObject.cpp
 )
source_group("composite" FILES ${compositeSource})

 
 
add_library(integration ${integrationSource} ${implementationSource} ${moduleSource} ${mbslibSource} ${compositeSource} ${historySource})
target_link_libraries(integration core common math)
project_folder("simulation/modules" integration)