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
#include "BallJoint.h"
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
	rungeKutta = new RungeKutta4(0.001);
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
	MiniGL::setViewport (40.0f, 1.0f, 100.0f, Vector3D (15.0, 1.0, 20.0), Vector3D (5.0, -4, 0.0));

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
  simulation.resetForces();

  // add forces acting at the first moment
  if (tm->getTime() < h) {
	  plank->addExternalForce(plank->getPosition()+Vector3D(1,0,0),Vector3D(0,200,0));
	  sphere->addExternalForce(sphere->getPosition(),Vector3D(300*3,150*2,0));
	  }

  /*for (vector<Particle*>::iterator it = particles.begin(); it!=particles.end(); it++)
	  (*it)->addExternalForce(Vector3D((rand()%100-50)*1.01,(rand()%100-50)*1.01,(rand()%100-50)*1.01));*/

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
  plank = new Box(0.5,3,0.5,1);

  double swingThickness = 0.03;
  double swingHeight = 4.5;
  double swingWidth = 1.5;
  RigidBody* swingSegment1 = new Box(1,swingThickness,swingHeight,swingThickness);	//left
  RigidBody* swingSegment2 = new Box(1,swingThickness,swingHeight,swingThickness);	// right
  RigidBody* swingSegment3 = new Box(0.5,swingWidth,swingThickness,swingThickness);	// seat
  Particle* swingHolder1 = new Particle();
  Particle* swingHolder2 = new Particle();
  
  cube->setPosition(Vector3D(0,2,0));
  cube2->setPosition(Vector3D(0,0,0));
  cube3->setPosition(cube2->getPosition() + Vector3D(0,-2,0));
  sphere->setPosition(Vector3D(1,1,0));
  plank->setPosition(Vector3D(3,-2,0));

  Vector3D swingOrigin(4,1,0);
  Quaternion q;
  double swingAngle = 8.0 * 3.14159265358979323846 / 180;
  q.setFromAxisAngle(Vector3D(1,0,0),-swingAngle);
  swingSegment1->setOrientation(q);
  swingSegment2->setOrientation(q);
  swingSegment1->setPosition(swingOrigin + Vector3D(-swingWidth/2,0,0));
  swingSegment2->setPosition(swingOrigin + Vector3D( swingWidth/2,0,0));
  swingSegment3->setPosition(swingOrigin + Vector3D(0,-cos(swingAngle) * swingHeight / 2,sin(swingAngle) * swingHeight / 2));
  swingHolder1->setPosition(swingOrigin + Vector3D(-swingWidth/2,cos(swingAngle)*swingHeight/2,-sin(swingAngle)*swingHeight / 2));
  swingHolder2->setPosition(swingOrigin + Vector3D( swingWidth/2,cos(swingAngle)*swingHeight/2,-sin(swingAngle)*swingHeight / 2));

swingHolder1->setMass(0);
swingHolder2->setMass(0);
  //for(int i=0 ;i <5; i++){
  //  Particle* p = new Particle();
  //  p->addExternalForce(Vector3D((rand()%100-50)*0.01,(rand()%100-50)*0.01,(rand()%100-50)*0.01));
  //  particles.push_back(p);
  //  simulation.addBody(p);
  //}

  simulation.addBody(cube);
  simulation.addBody(cube2);
  simulation.addBody(cube3);
  simulation.addBody(sphere);
  simulation.addBody(plank);

  simulation.addBody(swingSegment1);
  simulation.addBody(swingSegment2);
  simulation.addBody(swingSegment3);
  simulation.addBody(swingHolder1);
  simulation.addBody(swingHolder2);

  // Create damped springs
  // spring parameters
  Real restLength = 1.5;
  Real ks = 60;
  Real kd = 9;

  Real restLength2 = 1.5;
  Real ks2 = 40;
  Real kd2 = 1;

  DampedSpring *spring1, *spring2;
  
  Connector *c1 = new RigidBodyConnector(cube,new Vector3D(0,-0.5,0));
Connector *c2 = new RigidBodyConnector(cube2,new Vector3D(0.5,0.5,0));
Connector *c3 = new RigidBodyConnector(cube2,new Vector3D(0,-0.5,0));
Connector *c4 = new RigidBodyConnector(cube3,new Vector3D(0,0.5,0));
Connector *c5 = new ParticleConnector(swingHolder1);
Connector *c6 = new ParticleConnector(swingHolder2);
Connector *c7 = new RigidBodyConnector(swingSegment1,new Vector3D(swingHolder1->getPosition() - swingSegment1->getPosition()));
Connector *c8 = new RigidBodyConnector(swingSegment2,new Vector3D(swingHolder2->getPosition() - swingSegment2->getPosition()));
Vector3D swingBottomLeft(swingSegment3->getPosition()[0]-swingWidth/2,swingSegment3->getPosition()[1],swingSegment3->getPosition()[2]);
Vector3D swingBottomRight(swingSegment3->getPosition()[0]+swingWidth/2,swingSegment3->getPosition()[1],swingSegment3->getPosition()[2]);
Connector *c9 = new RigidBodyConnector(swingSegment1,new Vector3D(swingBottomLeft - swingSegment1->getPosition()));
Connector *c10 = new RigidBodyConnector(swingSegment3,new Vector3D(swingBottomLeft - swingSegment3->getPosition()));
Connector *c11 = new RigidBodyConnector(swingSegment3,new Vector3D(swingBottomRight - swingSegment3->getPosition()));
Connector *c12 = new RigidBodyConnector(swingSegment2,new Vector3D(swingBottomRight - swingSegment2->getPosition()));
simulation.addConnector(c1);
  simulation.addConnector(c2);
  simulation.addConnector(c3);
  simulation.addConnector(c4);
  simulation.addConnector(c5);
  simulation.addConnector(c6);
  simulation.addConnector(c7);
  simulation.addConnector(c8);
  /*simulation.addConnector(c9);
  simulation.addConnector(c10);
  simulation.addConnector(c11);
  simulation.addConnector(c12);*/

  spring1 = new DampedSpring(c1,c2,ks,kd,restLength);
  spring2 = new DampedSpring(c3,c4,ks2,kd2,restLength2);

  simulation.addForce(spring1);
  simulation.addForce(spring2);
  simulation.addForce(new Gravity());

  simulation.addJoint(new BallJoint(c5,c7));
  simulation.addJoint(new BallJoint(c6,c8));
  //simulation.addJoint(new BallJoint(c9,c10));
  //simulation.addJoint(new BallJoint(c11,c12));

  simulation.setIntegrator(rungeKutta);//explEuler);
}


void render ()
{
  MiniGL::coordinateSystem();
  
  // Draw simulation model
  simulation.render();

  MiniGL::drawTime( TimeManager::getCurrent ()->getTime ());
}

