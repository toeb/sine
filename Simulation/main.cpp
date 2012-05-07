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


#include "Common/Config.h"
#include "Visualization/MiniGL.h"
#include "GL/glut.h"
#include "TimeManager.h"
#include "Math/SimMath.h"
#include "Common/StringTools.h"
#include "Common/timing.h"
#include "Math/VectorND.h"
#include "SimulationObjects/RigidBody.h"
#include "SimulationObjects/Sphere.h"
#include "SimulationObjects/Box.h"
#include "Integrators/Integrator.h"
#include "Integrators/Implementations/ExplicitEuler.h"
#include "Integrators/Implementations/RungeKutta4.h"
#include "Integrators/Implementations/RungeKuttaFehlberg45.h"
#include "Integrators/CompositeIntegratable.h"
#include "SimulationObjects/Particle.h"
#include "Simulation.h"
#include "SimulationObjects/DampedSpring.h"
#include "SimulationObjects/RigidBodyConnector.h"
#include "SimulationObjects/ParticleConnector.h"
#include "SimulationObjects/Gravity.h"
#include "SimulationObjects/BallJoint.h"
#include "Simulation/CustomSimulation.h"
// Enable memory leak detection
#ifdef _DEBUG
  #define new DEBUG_NEW 
#endif

using namespace IBDS;
using namespace std;

void timeStep ();
void buildModel ();
void render ();
void cleanup();


Simulation * simulation;
Integrator *explEuler,*rungeKutta, *rungeKuttaFehlberg45;
IntegratorsManager* integratorsManager;

// main 
int main( int argc, char **argv )
	{
	REPORT_MEMORY_LEAKS
	USE_TIMESTEP_TIMING(Timing::m_dontPrintTimes = true;);

	// OpenGL
	/*
	// initialize the integrators
	explEuler = new ExplicitEuler();
	rungeKutta = new RungeKutta4(0.001);
	rungeKuttaFehlberg45 = new RungeKuttaFehlberg45();
	const int integratorsCount = 3;
  
	// initialize the manager
	Integrator* integrators[integratorsCount] = {explEuler, rungeKutta, rungeKuttaFehlberg45};
	integratorsManager = new IntegratorsManager(&simulation,integrators,integratorsCount);
	// connect the view to the integratorsManager, this must happen before MiniGL::init
	
  MiniGL::setIntegratorsManager(integratorsManager);
  */
  simulation = new CustomSimulation();

  simulation->setCommandLineArguments(argc,argv);

  simulation->initialize();

	MiniGL::init (argc, argv, 800, 600, 0, 0, "MiniGL");

	MiniGL::initLights ();		

//	buildModel ();

	MiniGL::setClientSceneFunc(render);			
	MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (15.0, 1.0, 20.0), Vector3D (5.0, -4, 0.0));
  
	MiniGL::setClientIdleFunc (50, timeStep);		
	glutMainLoop ();	



	cleanup ();

	USE_TIMESTEP_TIMING(printAverageTimes());

	return 0;
	}

void cleanup()
{
}


// the simulated bodies (the declaration is here because they are used across several methods)
RigidBody *cube, *cube2, *cube3, *sphere, *plank;
//vector<Particle*> particles;
//Particle* p1,*p2;

void timeStep ()
{
  START_TIMING("timeStep");

  TimeManager *tm = TimeManager::getCurrent ();
  const Real h = tm->getTimeStepSize();

  // Simulation code  
  simulation->simulate(tm->getTime()+h);

  // add forces acting at the first moment
  /*
  if (tm->getTime() < h) {
	  plank->addExternalForce(plank->getPosition()+Vector3D(1,0,0),Vector3D(0,200,0));
	  sphere->addExternalForce(sphere->getPosition(),Vector3D(300*3,150*2,0));
	  }
    */
  /*for (vector<Particle*>::iterator it = particles.begin(); it!=particles.end(); it++)
	  (*it)->addExternalForce(Vector3D((rand()%100-50)*1.01,(rand()%100-50)*1.01,(rand()%100-50)*1.01));*/


  tm->setTime(tm->getTime() + h);

  STOP_TIMING_AVG;
}


void render ()
{
  MiniGL::coordinateSystem();
  
  // Draw simulation model
  simulation->render();

  MiniGL::drawTime( TimeManager::getCurrent ()->getTime ());
}

