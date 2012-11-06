#include <application.sample.h>
#include <visualization.opengl.renderer.geometry.h>
#include <simulation.dynamics.h>
#include <simulation.utility/DynamicsAlgorithm.h>
using namespace nspace;
using namespace std;




class TrajectorySystemFunction : public virtual ISystemFunction, public virtual PropertyChangingObject{
  REFLECTABLE_OBJECT(TrajectorySystemFunction);
public:
  typedef Function<StateMatrix,Real> Trajectory;
  PROPERTY(Trajectory*, Trajectory){}
  PROPERTY(StatefulObject*, StatefulObject){}
public:
  
  TrajectorySystemFunction():_Trajectory(0),_StatefulObject(0){

  }
  virtual void evaluate(Time t, Time h){
    auto trajectory = getTrajectory();
    auto state=getStatefulObject();
    if(!trajectory)return;
    if(!state)return;
    VectorND x;
    trajectory->evaluate(x,t);

    //s.setState();


  }
};

class MySample : public Sample{
public:
  void setup(){
    auto algorithm = new DynamicsAlgorithm();

    auto body = new RigidBody();
    
    auto evaluator = new Evaluator(body->kinematics(),algorithm);
    application().getIntegrator()->setEvaluator(evaluator);
    auto f = new PiecewiseFunction<Vector3D>();
    
    MatrixNxM tmp(3,4);
    auto poly1=new Polynom<Vector3D,MatrixNxM>();
    tmp(0,0)=0;
    tmp(1,0)=0;
    tmp(2,0)=0;
    tmp(0,1)=1;
    tmp(1,1)=1;
    tmp(2,1)=1;
    tmp(0,2)=0;
    tmp(1,2)=0;
    tmp(2,2)=0;
    tmp(0,3)=0;
    tmp(1,3)=0;
    tmp(2,3)=0;
    poly1->setCoefficients(tmp);
    auto poly2=new Polynom<Vector3D,MatrixNxM>();
    tmp(0,0)=1;
    tmp(1,0)=1;
    tmp(2,0)=1;
    tmp(0,1)=-1;
    tmp(1,1)=-1;
    tmp(2,1)=-1;
    tmp(0,2)=1;
    tmp(1,2)=0;
    tmp(2,2)=0;
    tmp(0,3)=0;
    tmp(1,3)=0;
    tmp(2,3)=0;
    poly2->setCoefficients(tmp);
    f->add(0,poly1);
    f->add(1,poly2);
    f->add(2,poly1);
    f->add(3,poly2);
    f->add(4,poly1);
    f->add(5,poly2);
    f->add(6,poly1);
    f->add(7,poly2);
    f->add(8,poly1);
    f->add(9,poly2);
    f->add(10,poly1);
    f->add(11,poly2);
    f->add(12,poly1);
    f->add(13,poly2);
    f->add(14,poly1);
    
    // create a sphere with radius 0.5
    auto sphere = new Sphere(0.5);
    Time tacc=0;
    auto task = new ScheduledTaskDelegate<std::function<void(Time,Time)>>([&tacc,f,sphere](Time dt, Time t){
      tacc+=dt;
      f->evaluate(sphere->coordinates().position(),tacc);
    });
    //task->setInterval(0.001);
    //task->setIsOneTimeTask(false);
    Components()|=task;

    Components()|=algorithm;

    // create a sphere renderer
    auto sphereRenderer = new SphereRenderer();
    // add renderer to component set
    Components() |= sphereRenderer;

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