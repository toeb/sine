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
#include <visualization.opengl.renderer/GridRenderer.h>
#include <visualization.opengl.renderer/MeshGridRenderer.h>
#include <core/StringTools.h>
#include <visualization/RenderSet.h>
#include <visualization.opengl.renderer/LightRenderer.h>
#include <core/PropertyChangingObject.h>
using namespace nspace;
using namespace std;
using namespace std::extensions;




int main(int argc,  char ** argv){

  Color::loadColors("resources/colors/palette.txt");
  Hub hub;

  InitializationModule initializer;
  hub |= &initializer;

  hub.successorsToStream(cout);

  ViewportPlugin viewport2;
  hub|= &viewport2;
  QtTaskRunner taskRunner;
  hub |=&taskRunner;

  PluginApplication app(argc,argv);
  hub |= &app;


  ViewportPlugin viewportPlugin;
  hub |= &viewportPlugin;
  
  viewport2.glWidget()->setViewportController(new FpsCamera());  
  viewportPlugin.glWidget()->setViewportController(new FpsCamera());
  GlViewport glviewport;




  hub|=&glviewport;

  GlViewport glviewport2;
  glviewport2.setName("second view");
  hub|=&glviewport2; 
  glviewport2.clearColor().setTo("AliceBlue");
  glviewport.coordinates().position() = Vector3D(0,0,10);
  glviewport.coordinates().orientation().fromRollPitchYaw(0.0,0.0,scalar::pi<Real>());
  CoordinateSystemRenderer originRenderer(CoordinateSystem::identity());
  

  RenderSet renderset;

  hub |= &renderset;

  MeshGridRenderer renderer;

  hub |= & renderer;

  LightRenderer lights;
  hub |= &lights;
  
  glviewport.setRenderer(& renderset);
  glviewport2.setRenderer(&renderset);
  hub.successorsToStream(cout);
  app.run();
  return 0;
}