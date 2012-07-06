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
#include <GlutRunner/GlutSimulationRunner.h>
#include <Visualization/Renderers/SimulationRunnerRenderer.h>
#include <Visualization/UserInterface/DelegateAction.h>
#include "CustomSimulation.h"
#include <Visualization/MiniGL.h>
#include <Visualization/Renderers/TweakBar/TweakBarRenderer.h>

using namespace IBDS;
using namespace std;


// main 
int main( int argc, char **argv )
{

  auto simulation = new CustomSimulation();
  

  GlutSimulationRunner & runner = GlutSimulationRunner::instance();
  
  IAction * action = new DelegateAction("TogglePause", [&runner](){runner.togglePause();});
  
  
  simulation->add(action);

  runner.setCommandLineArguments(argc,argv);

  runner.setSimulation(simulation); 


  simulation->buildAlgorithms();
  simulation->buildModel();
    
  //MiniGL::drawMode = 0x1B01;

  auto integrable = simulation->getIntegrator()->getIntegratable();
  Real* initialState = new Real[integrable->getStateDimension()];
  integrable->getState(initialState);

  action = new DelegateAction("Reset",[initialState, integrable](){
    integrable->setState(initialState);
  });
  simulation->add(action);

  simulation->add(static_cast<IRenderer*>(new TweakBarRenderer()));
  
  runner.run();


	return 0;
	}