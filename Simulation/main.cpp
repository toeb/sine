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
#include "Integrators/Integrator.h"
#include "Integrators/Implementations/ExplicitEuler.h"
#include "Integrators/Implementations/RungeKutta4.h"
#include "Integrators/Implementations/RungeKuttaFehlberg45.h"
#include "Integrators/CompositeIntegratable.h"
#include "Particle.h"
#include "Simulation.h"
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
// main 
int main( int argc, char **argv )
{
  REPORT_MEMORY_LEAKS
  USE_TIMESTEP_TIMING(Timing::m_dontPrintTimes = true;);



  // OpenGL
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


void timeStep ()
{
  START_TIMING("timeStep");

  TimeManager *tm = TimeManager::getCurrent ();
  const Real h = tm->getTimeStepSize();

  // Simulation code
  
  simulation.simulate(tm->getTime()+h);

  tm->setTime(tm->getTime() + h);

  STOP_TIMING_AVG;
}
RigidBody * cube, *cube2;
RigidBody * fixedCube;

void buildModel ()
{
  TimeManager::getCurrent ()->setTimeStepSize (0.01);
  cube = RigidBody::createBox(1,1,1,1);
  cube2 = RigidBody::createBox(1,1,1,1);
  cube2->setPosition(Vector3D(0,1,0));
  fixedCube = RigidBody::createBox(0,1,1,1);
  //simulation.addSimulationObject(fixedCube);
  simulation.addSimulationObject(cube);
  simulation.addSimulationObject(cube2);
  //cube->addExternalTorqueWCS(Vector3D(0,0,1));
  cube->addExternalForce(Vector3D(0,1,0),Vector3D(1,0,0));
  cube2->addExternalForce(Vector3D(0,2,-0.5),Vector3D(0,0,-0.1));
 // cube->addExternalTorqueWCS(Vector3D(0,0.5,0.5));
  //cube->addExternalForceWCS(Vector3D(0.5,0.5,-0.5),Vector3D(0.1,-0.1,0));

  for(int i=0 ;i <5; i++){
   
    Particle* p = new Particle();
    p->addExternalForce(Vector3D((rand()%100-50)*0.01,(rand()%100-50)*0.01,(rand()%100-50)*0.01));
    particles.push_back(p);
    simulation.addSimulationObject(p);
  }
  simulation.setIntegrator(new ExplicitEuler());
  //simulation.setIntegrator(new RungeKutta4(0.01));
  //simulation.setIntegrator(new RungeKuttaFehlberg45());
  // Create simulation model
}


void render ()
{
  MiniGL::coordinateSystem();
  
  // Draw simulation model
  simulation.render();
  /*for(vector<Particle*>::iterator it = particles.begin(); it != particles.end(); it++){
    MiniGL::drawPoint((*it)->getPosition(),5,MiniGL::darkblue);
  }
  Matrix3x3 R;
  Quaternion q = cube->getOrientation();
  q.getMatrix3x3(R);
 
  Matrix3x3 R2;
  Quaternion q2 = cube2->getOrientation();
  q2.getMatrix3x3(R2);

  MiniGL::drawCube(&(cube->getPosition()), &R,1,1,1,MiniGL::darkGray);
  MiniGL::drawCube(&(cube2->getPosition()), &R2,1,1,1,MiniGL::darkGray);*/

  // MiniGL::drawCube(&(fixedCube->getPosition()), &R,1,1,1,MiniGL::darkGreen);
  MiniGL::drawTime( TimeManager::getCurrent ()->getTime ());
	/*	q = fixedCube->getOrientation();
  q.getMatrix3x3(R);
   MiniGL::drawCube(new Vector3D(1.0,1.0,0.0),new Matrix3x3(),1,1,1,MiniGL::blue);*/

}

