
add_files(../include/math.integration source)
add_files(Integrator source)
add_files(Stepper source)
add_files(IStepper source)
add_files(MultiStepSolver source)
add_files(IntegrableFunctionTraits source)
add_files(SingleStepSolver source)

source_group("" FILES ${source})

add_files(implementation/singlestep/RungeKutta2 singlestepSource)
add_files(implementation/singlestep/RungeKutta4 singlestepSource)
add_files(implementation/singlestep/RungeKuttaFehlberg45 singlestepSource)
add_files(implementation/singlestep/ExplicitEuler singlestepSource)
add_files(implementation/singlestep/ImplicitEuler singlestepSource)

source_group("implementation\\singlestep" FILES ${singlestepSource})

set(source ${source} ${singlestepSource})

 add_library(math.integration ${source} CMakeLists.txt)
 target_link_libraries(math.integration math.matrix)