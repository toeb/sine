#include "SampleApplication.h"
#include <iostream>
using namespace std;
using namespace nspace;


 SampleApplication::SampleApplication(int argc, char ** argv, Sample & sample, const std::string & resourceDirectory):_sample(sample),_application(argc,argv),_ResourceDirectory(resourceDirectory){
    setName("SampleApplication");
    Color::loadColors(resourceDirectory+"/colors/palette.txt");
    Material::loadMaterials(resourceDirectory+"/materials/palette.txt");
    _sample.setApplication(*this);
    
  } 

 void SampleApplication::printSetup(){
   
    hub().foreachElement([](Object* o){
       cout << o << endl;
    });
 }
 void SampleApplication::printHierarchy(){
   hub().successorsToStream(cout);
 }
 
 void SampleApplication::setup(){
     
    viewport().clearColor().setTo("LightGreen");
    _viewportPlugin.setName("Visualization Window");
    _glViewport.setName("Default View");

    _grid.GridMaterial() = Color("LightGrey");
    _grid.setSections(50);
    _grid.Coordinates().position().y()=-5;
    _grid.setWidth(100);
    _grid.setHeight(100);

    _skybox.setFileBase(ResourceDirectory()+"/images/sky");

    hub()|=&_grid;
   // hub()|=&_skybox;
    hub()|=&_application;
    hub()|=&_initializer;
    hub()|=&_viewportPlugin;
    hub().add(&_Camera);
    hub()|=&_lights;
    hub()|=&_glViewport;
    hub()|=&_taskrunner;
    hub()|=&_renderers;
    hub()|= &_sample;
    _glViewport.setViewportRenderer(&_renderers);
    _viewportPlugin.glWidget()->setViewportController(&_Camera);

    viewport().Coordinates().position()=Vector3D(0,0,-10);
  }
  Hub & SampleApplication::hub(){return _hub;}
  GlViewport & SampleApplication::viewport(){return _glViewport;}
  
  
  int SampleApplication::run(){
    setup();
    _sample.setup();
    _initializer.initialize();
    return _application.run();
  }
