#include <application.sample.h>
#include <visualization.opengl.renderer.geometry.h>

using namespace nspace;


class MySample : public Sample{
public:
  
  void setup(){
    // create a sphere renderer
    auto sphereRenderer = new SphereRenderer();
    // add renderer to component set
    components() |= sphereRenderer;

    // create a sphere with radius 0
    auto sphere = new Sphere(0.5);

    // add sphere to renderer
    *sphereRenderer |= sphere;
    
    // print setup of sample app
    application().printSetup();
    application().printHierarchy();
  }  
};

int main(int argc,  char ** argv){
  // instanciate sample
  MySample sample;

  // create sample application
  SampleApplication app(argc,argv, sample);
  
  // run sample application
  return app.run();
}