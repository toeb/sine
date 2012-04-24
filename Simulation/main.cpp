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
#include "RigidBody.h"
#include "Sphere.h"
#include "Box.h"
#include "Integrators/Integrator.h"
#include "Integrators/Implementations/ExplicitEuler.h"
#include "Integrators/Implementations/RungeKutta4.h"
#include "Integrators/Implementations/RungeKuttaFehlberg45.h"
#include "Integrators/CompositeIntegratable.h"
#include "Particle.h"
#include "Simulation.h"
#include "DampedSpring.h"
#include "RigidBodyConnector.h"
#include "ParticleConnector.h"
#include "Gravity.h"
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

Simulation simulation;
vector<Particle*> particles;
Integrator *explEuler,*rungeKutta, *rungeKuttaFehlberg45;
IntegratorsManager* integratorsManager;

// main 
int main( int argc, char **argv )
	{
	REPORT_MEMORY_LEAKS
	USE_TIMESTEP_TIMING(Timing::m_dontPrintTimes = true;);

	// OpenGL
	
	// initialize the integrators
	explEuler = new ExplicitEuler();
	rungeKutta = new RungeKutta4(0.01);
	rungeKuttaFehlberg45 = new RungeKuttaFehlberg45();
	const int integratorsCount = 3;

	// initialize the manager
	Integrator* integrators[integratorsCount] = {explEuler, rungeKutta, rungeKuttaFehlberg45};
	integratorsManager = new IntegratorsManager(&simulation,integrators,integratorsCount);
	// connect the view to the integratorsManager, this must happen before MiniGL::init
	MiniGL::setIntegratorsManager(integratorsManager);

	MiniGL::init (argc, argv, 800, 600, 0, 0, "MiniGL");

	MiniGL::initLights ();
	MiniGL::setClientIdleFunc (50, timeStep);				

	buildModel ();

	MiniGL::setClientSceneFunc(render);			
	MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (3.0, 1.0, 10.0), Vector3D (3.0, -0.3, 0.0));

	glutMainLoop ();	

	cleanup ();

	USE_TIMESTEP_TIMING(printAverageTimes());

	return 0;
	}

void cleanup()
{
}


RigidBody *cube, *cube2, *cube3, *sphere;
Particle* p1,*p2;

void timeStep ()
{
  START_TIMING("timeStep");

  TimeManager *tm = TimeManager::getCurrent ();
  const Real h = tm->getTimeStepSize();

  // Simulation code
  simulation.resetForces();

  if (tm->getTime() < 0.00001)
	    sphere->addExternalForce(sphere->getPosition(),Vector3D(300*3,150*2,0));
  
  simulation.simulate(tm->getTime()+h);

  tm->setTime(tm->getTime() + h);

  STOP_TIMING_AVG;
}

void buildModel ()
{
  // create objects, set their mass and position
  TimeManager::getCurrent ()->setTimeStepSize (0.01);

  cube = new Box(0,1,1,1);
  cube2 = new Box(1,1,1,1);
  cube3 = new Box(1,1,1,1);
  sphere = new Sphere(1,0.5);
  
  p1 = new Particle();
  p1->setMass(0);
  p2 = new Particle();

  cube->setPosition(Vector3D(0,2,0));
  cube2->setPosition(Vector3D(0,0,0));
  sphere->setPosition(Vector3D(1,1,0));
  cube3->setPosition(cube2->getPosition() + Vector3D(0,-2,0));

  p1->setPosition(Vector3D(-1,1.5,0));
  p2->setPosition(Vector3D(-1.2,0.5,0));


 // cube->addExternalForce(Vector3D(0,1,0),Vector3D(1,0,0));
 // cube2->addExternalForce(Vector3D(0,2,-0.5),Vector3D(0,0,-0.1));

  for(int i=0 ;i <5; i++){
    Particle* p = new Particle();
    p->addExternalForce(Vector3D((rand()%100-50)*0.01,(rand()%100-50)*0.01,(rand()%100-50)*0.01));
    particles.push_back(p);
    simulation.addBody(p);
  }

  simulation.addBody(cube);
  simulation.addBody(cube2);
  simulation.addBody(cube3);
  simulation.addBody(sphere);
  simulation.addBody(p1);
  simulation.addBody(p2);

  // Create damped springs
  // spring parameters
  Real restLength = 1.5;
  Real ks = 60;
  Real kd = 9;

  Real restLength2 = 1.5;
  Real ks2 = 40;
  Real kd2 = 1;

  DampedSpring *spring, *spring2, *spring3;

  spring = new DampedSpring(new ParticleConnector(p1),new ParticleConnector(p2),ks,kd,restLength);
  spring2 = new DampedSpring(new RigidBodyConnector(cube,new Vector3D(0,-0.5,0)),new RigidBodyConnector(cube2,new Vector3D(0,0.5,0)),ks,kd,restLength);
  spring3 = new DampedSpring(new RigidBodyConnector(cube2,new Vector3D(0,-0.5,0)),new RigidBodyConnector(cube3,new Vector3D(0,0.5,0)),ks2,kd2,restLength2);

  simulation.addForce(spring);
  simulation.addForce(spring2);
  simulation.addForce(spring3);
  simulation.addForce(new Gravity());

  simulation.setIntegrator(explEuler);
}


void render ()
{
  MiniGL::coordinateSystem();
  
  // Draw simulation model
  simulation.render();

  MiniGL::drawTime( TimeManager::getCurrent ()->getTime ());
}

