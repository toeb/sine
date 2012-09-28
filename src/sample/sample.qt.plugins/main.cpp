#include <application.qt/PluginApplication.h>
#include <simulation/Simulation.h>
#include <simulation.time/PeriodicTask.h>
#include <simulation.runner.qt/QtViewport.h>
#include <simulation.runner.qt/QtTaskRunner.h>
#include <core.hub/Hub.h>
#include <visualization.opengl.renderer.geometry/CoordinateSystemRenderer.h>
#include <iostream>
using namespace nspace;
using namespace std;

int main(int argc,  char ** argv){
  Hub hub;
  
  QtViewport viewport2;
  hub<< viewport2;


  QtTaskRunner taskRunner;
  hub <<taskRunner;

  PluginApplication app(argc,argv);
  hub << app;

  
  QtViewport viewport;
  hub << viewport;

  
  CoordinateSystemRenderer originRenderer(CoordinateSystem::identity());
  //viewport << originRenderer;

  app.run();
  return 0;
}