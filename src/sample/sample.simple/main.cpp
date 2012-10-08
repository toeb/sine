#include <application.sample.h>

#include <visualization.opengl.renderer.geometry.h>


#include <iostream>

using namespace nspace;
using namespace std;
class MySample : public Sample{
public:
  
  void setup(){
    application().viewport().clearColor().setTo("LightGreen");
    components() |= new MeshGridRenderer();    
    components() |= new GridRenderer(0.0);
    
    auto sphereRenderer = new SphereRenderer();
    auto sphere = new Sphere(0.5);
    *sphereRenderer |= sphere;

    components() |= new SkyboxRenderer(application().getResourceDirectory()+"/images/landscape1");
    components() |= sphereRenderer;

    Vector3D & cameraPosition = application().viewport().coordinates().position();

    Real & angle = *new Real;
    angle =0.0;
    
    auto task = new ScheduledTaskDelegate([&angle,this](Time dt, Time t){
      angle+=dt;
      application().viewport().coordinates().orientation().fromRollPitchYaw(0.0,0.0,angle);
    });
    task->interval() = 0.01;
    task->isOneTimeTask() = false;

    //components()|= task;


    application().viewport().coordinates().position() = Vector3D(0,0,10);
    application().viewport().coordinates().orientation().fromRollPitchYaw(0.0,0.0,scalar::pi<Real>());
    //application().hub().successorsToStream(cout);
    application().hub().foreachElement([](Object* o){
      cout << o << endl;
    });
  }  
};

int main(int argc,  char ** argv){
  MySample sample;
  SampleApplication app(argc,argv, sample);

  return app.run();
}