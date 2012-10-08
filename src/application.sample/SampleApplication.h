#pragma once
#include <application.sample.h>
#include <core.hub.h>
#include <application.qt.h>
#include <core.initialization.h>
#include <visualization.opengl.qt.h>
#include <visualization.h>
#include <visualization.opengl.renderer.h>
#include <simulation.runner.qt/QtTaskRunner.h>
#include <visualization/Material.h>


namespace nspace{
class SampleApplication : public virtual NamedObject{
private:
  Hub _hub;
  PluginApplication _application;
  InitializationModule _initializer;
  ViewportPlugin _viewportPlugin;
  FpsCamera _Camera;
  GlViewport _glViewport;
  RenderSet _renderers;
  QtTaskRunner _taskrunner;
  Sample & _sample;
  DefaultLightSetup _lights;
  SkyboxRenderer _skybox;
  GridRenderer _grid;

  REFERENCE_PROPERTY(SkyboxRenderer,skybox);
  REFERENCE_PROPERTY(FpsCamera,Camera);
  SIMPLE_PROPERTY(std::string, ResourceDirectory){}
  REFERENCE_PROPERTY(std::string, ResourceDirectory);
public:
  SampleApplication(int argc, char ** argv, Sample & sample, const std::string & resourceDirectory = ".");
  Hub & hub();
  GlViewport & viewport();
  
   void setup();
  int run();
  void printSetup();
  void printHierarchy();
};
}
