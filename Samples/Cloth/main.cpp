/*
 * IBDS - Impulse-Based Dynamic Simulation Library
 * Copyright (c) 2003-2008 Jan Bender http://www.impulse-based.de
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Jan Bender - Jan.Bender@impulse-based.de
 */

#include "Common/StringTools.h"
#include "Common/timing.h"
#include "CustomSimulation.h"
#include <GlutRunner/GlutSimulationRunner.h>
#include <Visualization/Renderers/SimulationRunnerRenderer.h>
#include <Visualization/UserInterface/DelegateAction.h>
// Enable memory leak detection
#ifdef _DEBUG
  #define new DEBUG_NEW 
#endif

using namespace IBDS;
using namespace std;

// main 
int main( int argc, char **argv )
	{
	REPORT_MEMORY_LEAKS
	USE_TIMESTEP_TIMING(Timing::m_dontPrintTimes = true;);

  auto simulation = new CustomSimulation();
  

  GlutSimulationRunner & runner = GlutSimulationRunner::instance();
  
  IAction * action = new DelegateAction("TogglePause", [&runner](){runner.togglePause();});
  
  
  simulation->addSimulationObject(action);

  runner.setCommandLineArguments(argc,argv);

  runner.setSimulation(simulation); 

  // this order has to be maintaned.  i'll need to fix this.
  simulation->buildAlgorithms();
  simulation->buildModel();
    

  auto integrable = simulation->getIntegrator()->getIntegratable();
  Real* initialState = new Real[integrable->getStateDimension()];
  integrable->getState(initialState);

  action = new DelegateAction("Reset",[initialState, integrable](){
    integrable->setState(initialState);
  });
  simulation->addSimulationObject(action);

  
  runner.run();


	USE_TIMESTEP_TIMING(printAverageTimes());

	return 0;
	}