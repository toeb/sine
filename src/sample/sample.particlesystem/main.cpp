#include <application.sample.h>
#include <visualization.opengl.renderer.geometry.h>
#include <simulation.dynamics.h>
#include <simulation.utility/DynamicsAlgorithm.h>
using namespace nspace;
using namespace std;


template <typename MatrixType> void random(MatrixType & matrix){
  for(int i=0; i< rows(matrix); i++){
    for(int j=0; j < cols(matrix); j++){
      coefficient(matrix,i,j)=(rand()%1000)/1000.0-0.5;
    }
  }
}

class MySample : public Sample, public virtual PropertyChangingObject, public virtual NamedObject{
  REFLECTABLE_OBJECT(MySample);
public:
  MySample():_Renderer(0){setName("MySample");}


  OBJECTPOINTERCOLLECTION(Particle, Particles,{
    auto sphere = new Sphere();
    sphere->setRadius(0.1);    
    sphere->coordinates().position.mirror(item->position);
    getRenderer()->add(sphere);
  },
  {    
  });

  OBJECTPOINTERPROPERTY(SphereRenderer, Renderer){if(oldvalue)Components()/=oldvalue; Components()|=newvalue;}

  void setup(){
    setRenderer(new SphereRenderer());
    
    // generate a couple of particles
    for(int i=0;i < 100; i++){
      auto particle = new Particle();
      random(particle->position());
      particle->position()*=40.0;
      random(particle->velocity());
      Particles().add(particle);
    }


    


  }
  
};

int main(int argc,  char ** argv)
{
  // instanciate sample
  MySample sample;
  // create sample application
  SampleApplication app(argc,argv, sample);
  // run sample application
  return app.run();
}
