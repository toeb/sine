#include <application.qt/PluginApplication.h>
#include <simulation/Simulation.h>
#include <simulation.time/PeriodicTask.h>
#include <visualization.opengl.qt/ViewportPlugin.h>
#include <simulation.runner.qt/QtTaskRunner.h>
#include <core.hub/Hub.h>
#include <visualization.opengl.renderer.geometry/CoordinateSystemRenderer.h>
#include <core.initialization/InitializationModule.h>
#include <iostream>
using namespace nspace;
using namespace std;

int main(int argc,  char ** argv){
  Hub hub;
  
  InitializationModule initializer;
  hub << initializer;


  ViewportPlugin viewport2;
  hub<< viewport2;


  QtTaskRunner taskRunner;
  hub <<taskRunner;

  PluginApplication app(argc,argv);
  hub << app;

  
  ViewportPlugin viewport;
  hub << viewport;

  
  CoordinateSystemRenderer originRenderer(CoordinateSystem::identity());
  
  app.run();
  return 0;
}