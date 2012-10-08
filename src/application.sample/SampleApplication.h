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
class SampleApplication{
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

  REFERENCE_PROPERTY(FpsCamera,Camera);
  PROPERTY(std::string, ResourceDirectory){}

public:
  SampleApplication(int argc, char ** argv, Sample & sample, const std::string & resourceDirectory = "resources"):_sample(sample),_application(argc,argv),_ResourceDirectory(resourceDirectory){
    Color::loadColors(resourceDirectory+"/colors/palette.txt");
    Material::loadMaterials(resourceDirectory+"/materials/palette.txt");
    _sample.setApplication(*this);
  }
  Hub & hub(){return _hub;}
  GlViewport & viewport(){return _glViewport;}
  
   void setup(){
    _viewportPlugin.setName("Visualization Window");
    hub()|=&_application;
    hub()|=&_initializer;
    hub()|=&_viewportPlugin;
    hub()|=&_Camera;
    hub()|=&_lights;
    hub()|=&_glViewport;
    hub()|=&_taskrunner;
    hub()|=&_renderers;
    hub()|= &_sample;
    _glViewport.setRenderer(&_renderers);
    _viewportPlugin.glWidget()->setViewportController(&_Camera);
    _glViewport.setName("Default View");
  }
  int run(){
    setup();
    _sample.setup();
    _initializer.initialize();
    return _application.run();
  }

};
}