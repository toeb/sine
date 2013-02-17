#pragma once

#include <math.integration/IntegrableFunctionTraits.h>
#include <math.integration/IStepper.h>
#include <math.integration/Stepper.h>

#include <math.integration/implementation/singlestep/ExplicitEuler.h>
#include <math.integration/implementation/singlestep/ImplicitEuler.h>
#include <math.integration/implementation/singlestep/RungeKutta2.h>
#include <math.integration/implementation/singlestep/RungeKutta4.h>
#include <math.integration/implementation/singlestep/RungeKuttaFehlberg45.h>