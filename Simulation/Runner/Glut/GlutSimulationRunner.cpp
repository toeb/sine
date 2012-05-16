#include "GlutSimulationRunner.h"
#include <Visualization/MiniGL.h>
#include <freeglut/include/GL/glut.h>
#include <iostream>
#include <Common/timing.h>
using namespace IBDS;
using namespace std;

static GlutSimulationRunner* runnerInstance =0;

const static string glutTimerName("glutSimulationTimer");

GlutSimulationRunner* GlutSimulationRunner::instance(){
  if(!runnerInstance)runnerInstance = new GlutSimulationRunner();
  return runnerInstance;
}


GlutSimulationRunner::GlutSimulationRunner(): _commandlineArgumentArray(0), _commandlineArgumentCount(0){

}

void timeStepGlutCallback ()
{
  if(runnerInstance==0){
    cerr<<"runner instance is not set. programmer error "<<endl;
    return;
  }
  
  runnerInstance->simulateCallback();
}
void renderGlutCallback(){
  if(runnerInstance==0){
    cerr<<"runner instance is not set. programmer error "<<endl;
    return;
  }
  runnerInstance->renderCallback();
}
void GlutSimulationRunner::run(){
  initialize();
  START_TIMING(glutTimerName);
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

void GlutSimulationRunner::cleanup(){
  getSimulation()->cleanup();
  getRenderers().cleanup();
}
bool GlutSimulationRunner::initialize(){  
  Simulation * simulation = getSimulation();
  if(!simulation){
    cerr << "GlutSimulationRunner::initialize:  Simulation is not set" << endl;
    return false;
  }
 
  if(! simulation->initialize()){
        cerr << "GlutSimulationRunner::initialize:  Simulation could not be initialised" << endl;
    return false;
  }

  
  const char * simulationName = getSimulationName(simulation);
  

  MiniGL::init (_commandlineArgumentCount, _commandlineArgumentArray, 800, 600, 0, 0, simulationName);
  MiniGL::setClientSceneFunc(renderGlutCallback);
  
  onDesiredTimeStepChanged(); //sets the simulationcallback

  
  
  

 if(!SimulationRunner::initialize())return false;
 if(! RenderEngine::initialize())return false;

 return true;
}

void GlutSimulationRunner::onSimulationSet(){
  RenderManager * renderMan = dynamic_cast<RenderManager*>(getSimulation());
  if(renderMan){
    setRenderManager(renderMan);
  }
}

void GlutSimulationRunner::renderCallback(){
  render();

}
void GlutSimulationRunner::simulateCallback(){
  Real timePassed = STOP_TIMING(glutTimerName);
  timePassed /= 1000;
  START_TIMING(glutTimerName);
  Simulation & simulation = *(getSimulation());
  Real time = simulation.getTime();
  if(timePassed > getDesiredTimeStepSize()){
    //cout << "failed realtime by " <<(timePassed -getDesiredTimeStepSize())<<" [s]"<<endl;
    timePassed = getDesiredTimeStepSize();
  }
  time += getDesiredTimeStepSize();

  simulation.simulate(time);
}