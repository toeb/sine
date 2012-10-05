#include <application.qt/PluginApplication.h>
#include <simulation/Simulation.h>
#include <simulation.time/PeriodicTask.h>
#include <visualization.opengl.qt/ViewportPlugin.h>
#include <simulation.runner.qt/QtTaskRunner.h>
#include <core.hub/Hub.h>
#include <visualization.opengl.renderer.geometry/CoordinateSystemRenderer.h>
#include <core.initialization/InitializationModule.h>
#include <visualization.opengl/GlViewport.h>
#include <visualization/Color.h>
#include <visualization.opengl/FpsCamera.h>
#include <iostream>
using namespace nspace;
using namespace std;




int main(int argc,  char ** argv){
  Color::loadColors("resources/colors/palette.txt");

  Hub hub;

  InitializationModule initializer;
  hub |= &initializer;


  ViewportPlugin viewport2;
  hub|= &viewport2;


  QtTaskRunner taskRunner;
  hub |=&taskRunner;

  PluginApplication app(argc,argv);
  hub |= &app;


  ViewportPlugin viewportPlugin;
  hub |= &viewportPlugin;

  DelegateKeyListener listener([](Keys key, DelegateKeyListener::KeyState state){
    std::cout << key << " " << state << std::endl;
  });
  hub |= &listener;

  viewportPlugin.glWidget()->setViewportController(new FpsCamera());
  GlViewport glviewport;


  hub|=&glviewport;

  hub.toString(cout);
  GlViewport glviewport2;
  glviewport2.setName("second view");
  hub|=&glviewport2; 
  glviewport2.clearColor().setTo("red");
  glviewport.coordinates().position() = Vector3D(0,0,10);
  glviewport.coordinates().orientation().fromRollPitchYaw(0.0,0.0,scalar::pi<Real>());
  CoordinateSystemRenderer originRenderer(CoordinateSystem::identity());
  glviewport.setRenderer(&originRenderer);
  app.run();
  return 0;
}