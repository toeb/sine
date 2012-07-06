#include "GlutSimulationRunner.h"
#include <Visualization/MiniGL.h>
#include <freeglut/include/GL/glut.h>
#include <freeglut/include/GL/freeglut_ext.h>
#include <iostream>
#include <Common/timing.h>
#include <GlutRunner/GlutRendererManager.h>
using namespace IBDS;
using namespace std;

static GlutSimulationRunner* runnerInstance =0;
const static string glutTimerName("glutSimulationTimer");

GlutSimulationRunner& GlutSimulationRunner::instance(){
  if(!runnerInstance)runnerInstance = new GlutSimulationRunner();
  return *runnerInstance;
}

GlutSimulationRunner::GlutSimulationRunner(): _commandlineArgumentArray(0), _commandlineArgumentCount(0){

}

void timeStepGlutCallback ()
{
  GlutSimulationRunner::instance().simulateCallback();
}

void GlutSimulationRunner::run(){
  initialize();
	glutMainLoop();	
  cleanup();
}

void GlutSimulationRunner::onDesiredTimeStepChanged(){
  int hz = 1000;
	Real dt = getDesiredTimeStepSize();
  if(dt>=0){
    Real realHz = 1/dt;
    hz = static_cast<int>(realHz);
  }
  MiniGL::setClientIdleFunc (hz, timeStepGlutCallback);		
}

void GlutSimulationRunner::onDesiredFramerateChanged(){
  cerr << "Glut does not have functionality allowing the framerate to change"<<endl;
}
char ** GlutSimulationRunner::getCommandLineArguments(int & argc){
  argc = _commandlineArgumentCount;
  return _commandlineArgumentArray;
}

void GlutSimulationRunner::setCommandLineArguments(int argc, char ** argv){
  _commandlineArgumentCount = argc;
  _commandlineArgumentArray= argv;
}

void GlutSimulationRunner::cleanupObject(){
  getSimulation()->cleanup();
  GlutInputHandler::instance().cleanup();
  GlutRenderer::instance().cleanup();
}

bool GlutSimulationRunner::initializeRunner(){  
  Simulation * simulation = getSimulation(); 
  const char * simulationName = getSimulationName(simulation);
  
  MiniGL::init (_commandlineArgumentCount, _commandlineArgumentArray, 800, 600, 0, 0, simulationName);

  onDesiredTimeStepChanged(); //sets the simulationcallback
  
  simulation->add(&(GlutInputHandler::instance()));
  simulation->add(&(GlutRenderer::instance()));

  if(!GlutRenderer::instance().initialize())return false;
 return true;
}

void GlutSimulationRunner::onSimulationSet(){

}

void GlutSimulationRunner::simulateCallback(){
  doTimestep(getDesiredTimeStepSize());
}