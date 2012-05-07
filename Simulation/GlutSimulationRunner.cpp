#include "GlutSimulationRunner.h"
#include <Visualization/MiniGL.h>
#include <freeglut/include/GL/glut.h>
#include <iostream>

using namespace IBDS;
using namespace std;

static GlutSimulationRunner* runnerInstance =0;

GlutSimulationRunner* GlutSimulationRunner::instance(){
  if(!runnerInstance)runnerInstance = new GlutSimulationRunner();
  return runnerInstance;
}

GlutSimulationRunner::GlutSimulationRunner(){

}

void timeStepCallback ()
{
  if(runnerInstance==0){
    cerr<<"runner instance is not set. programmer error "<<endl;
    return;
  }
}

void GlutSimulationRunner::run(){
  onDesiredTimeStepChanged();
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
  MiniGL::setClientIdleFunc (hz, timeStepCallback);		
}