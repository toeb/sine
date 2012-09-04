#include <ds.h>
#include <visualization/glrenderers/general/GridRenderer.h>
#include <visualization/glrenderers/general/LightRenderer.h>
#include <visualization/glrenderers/geometry/PolygonRenderer.h>
#include <simulation/geometry/Primitives/Hexahedron.h>
#include <simulation/kinematics/KinematicCoordinates.h>
#include <visualization/glrenderers/geometry/BoxRenderer.h>
#include <gl/glut.h>
#include <visualization/core/Color.h>
#include <visualization/glrenderers/general/BillboardRenderer.h>
#include <simulation/geometry/Plane.h>
#include <simulation/history/HistoryModule.h>
#include <common/patterns/Singleton.h>
#include <simulation/force/ForceField.h>
#include <simulation/dynamics/Particle.h>
#include <visualization/glrenderers/geometry/PointRenderer.h>
#include <simulation/dynamics/DynamicBodyModule.h>
#include <simulation/force/ForceModule.h>
#include <simulation/utility/DynamicsAlgorithm.h>
#include <simulation/force/Gravity.h>
#include <simulation/dynamics/RigidBody.h>
#include <simulation/dynamics/primitives/DynamicBox.h>
#include <simulation/geometry/Primitives/Sphere.h>
#include <visualization/glrenderers/geometry/SphereRenderer.h>
#include <simulation/multibody/impulsebased/ImpulseBasedMultiBodyModule.h>
#include <simulation/dynamics/connection/RigidBodyConnector.h>
#include <simulation/dynamics/connection/ConnectorFactory.h>
#include <readers/urdf/UrdfModelReader.h>
#include <simulation/model/builder/ModelBuilderBase.h>
#include <simulation/multibody/impulsebased/joints/BallJoint.h>
#include <simulation/time/CallbackTask.h>
#include <simulation/time/PeriodicTask.h>
using namespace nspace;
using namespace std;
class GlutObject : public virtual IRenderer{
  TYPED_OBJECT;
private:
  int _argc;
  char ** _argv;  
public:
  GlutObject(int argc, char ** argv):_argc(argc),_argv(argv){}
  bool initializeObject() 
  {
    glutInit(&_argc,_argv);
    return true;
  }

  void cleanupObject(){
    //glutExit();
  }
};


class ConnectorImpulseRenderer : public IRenderer{
private:
  RigidBodyConnector & connector;
public:
  ConnectorImpulseRenderer(RigidBodyConnector & connector):connector(connector){

  }
  void render(){
    MiniGL::drawVector(connector.getWorldPosition(), connector.lastImpulse*0.1+connector.getWorldPosition(),2,MiniGL::blue);
    connector.lastImpulse.setZero();
  }

};

class DSLibModelBuilder : public ModelBuilderBase{
private:
  CompositeSimulationObject _objects;
public:
  CompositeSimulationObject & simulationObjects(){
    return _objects;
  }

protected:
  
  void buildModel(Model & model){     
    model.nodes().foreachElement([this](Node * node){
      convertBody(node);
    });
    model.nodes().foreachElement([this](Node * node){
      convertConnector(node);
    });
    model.nodes().foreachElement([this](Node * node){
      convertConnection(node);
    });
    std::cout << model;
  }
    
private:
  void convertConnector(Node * node){
    Connector * connector =0;
    node->get(connector,"connector");
    if(!connector)return;

  }
  void convertConnection(Node * node){
    Connection * connection=0;
    node->get(connection,"connection");
    if(!connection)return;


  }
  void convertBody(Node * node){
    Body * body=0;
    node->get(body,"body");
    if(!body)return;

    RigidBody * rigidBody = new RigidBody();
    rigidBody->setMass(body->mass);
    rigidBody->setInertiaTensor(body->inertia);
    rigidBody->setName(node->name());


    CoordinateSystem initialCoordinates;
    node->get(initialCoordinates,"initialcoordinates");

    rigidBody->coordinates() = initialCoordinates;

    Sphere * sphere = new Sphere();
    sphere->coordinates().position.mirror(rigidBody->kinematics().position);
    _objects.addComponent(new  SphereRenderer(*sphere));
    
    _objects.addComponent(rigidBody);
  }

};

class MyDependentValue : public DependentValue<int>{
private:
  TypedObservableValue<int> & _original;
public:
  MyDependentValue(TypedObservableValue<int> & orig):_original(orig){
    dependencies().add(&orig);
  }
protected:
  int calculate(){
    return _original()+5;
  }
};

int main(int argc, char** argv){

  DefaultSimulationSetup setup;

  QtSimulationRunner runner;
  Simulation simulation;
  simulation.initialize();
  
 simulation << setup;
  
  RigidBody b1;
  RigidBody b2;
  RigidBody b3;

  b1.setMass(0);
  b2.setMass(1);
  b2.setInertiaTensor(Matrix3x3::Identity());
  b3.setMass(1);
  b3.setInertiaTensor(Matrix3x3::Identity());

  TypeId rb = b1.getBodyType();
  TypeId pt = Particle::ClassType();
  TypeId rbt = RigidBody::ClassType();
  b2.coordinates().position() = Vector3D(1,0,0);
  b3.coordinates().position()= Vector3D(2,0,0);
  RigidBodyConnector * c1 = ( RigidBodyConnector*)ConnectorFactory::instance().createWithWorldConnectionPoint(b1,Vector3D(0,0,0));
  RigidBodyConnector * c2 = ( RigidBodyConnector*)ConnectorFactory::instance().createWithWorldConnectionPoint(b2,Vector3D(0,0,0)); 
  RigidBodyConnector * c3 = ( RigidBodyConnector*)ConnectorFactory::instance().createWithWorldConnectionPoint(b2,Vector3D(1,0,0));
  RigidBodyConnector * c4 = ( RigidBodyConnector*)ConnectorFactory::instance().createWithWorldConnectionPoint(b3,Vector3D(1,0,0));
   
  simulation << new BallJoint(*c3,*c4);
  simulation << new BallJoint(*c1,*c2);
  
  simulation << new ConnectorImpulseRenderer(*c1);
  simulation << new ConnectorImpulseRenderer(*c2);
  simulation << new ConnectorImpulseRenderer(*c3);
  simulation << new ConnectorImpulseRenderer(*c4);
  
  simulation << b1;
  simulation << b2;
  simulation << b3;

  simulation << c1;
  simulation << c2;
  simulation << c3;
  simulation << c4;


  Hexahedron * box = new Hexahedron(0.5,0.5,0.5);
  box->coordinates().mirror(b1.coordinates());
  simulation << box;
  simulation << new BoxRenderer(*box);

  Hexahedron * box2 = new Hexahedron(0.5,0.5,0.5);
  box2->coordinates().mirror(b2.coordinates());
  simulation << box2;
  simulation << new BoxRenderer(*box2);

  Hexahedron * box3 = new Hexahedron(0.5,0.5,0.5);
  box3->coordinates().mirror(b3.coordinates());
  simulation << box3;
  simulation << box3;
  simulation << new BoxRenderer(*box3);
/*
  simulation << new PeriodicTaskDelegate([b2](Time t,Time dt){
    cout << t << ": " << b2.coordinates().position() << endl;
  },1.0,true);
*/



  UrdfModelReader & urdfReader = UrdfModelReader::instance();
  
  
  DSLibModelBuilder builder;

  bool result = urdfReader.parseFile(builder,"resources/models/model1.urdf");

  simulation << builder.simulationObjects();
  

  {

  int n(0), m(10), l(10);
  for(int j=0; j < n; j++){
    for(int i=0; i< m; i++){
      for(int k=0; k < l; k++){
        Hexahedron * box = new Hexahedron(2,2,2);
        KinematicBody * body=new KinematicBody();
        body->position()(0) = i*3-m/2*3;
        body->position()(1) = j* 3-n/2*3;
        body->position()(2) = k* 3-n/2*3;
        body->angularVelocity() = Vector3D(0.3,0,0);
        box->coordinates().mirror(*body);
        simulation << body;
        simulation << box;
        simulation << new BoxRenderer(*box);
      }
    }
  }
  }
  DynamicsAlgorithm da;
  simulation << new Gravity(1);
  

  

 /* simulation << new ForceField([](Vector3D & force, Vector3D & torque, const Vector3D & cog, Time t){
    if(cog.length2()<1){
 //    force = Vector3D(0,2,0);// - Vector3D::UnitX()*cog.x()*0.01 - Vector3D::UnitZ()*cog.z()*0.01;
    }
    //Vector3D rando ((rand()%1000)/1000.0-0.5,(rand()%1000)/1000.0-0.5,(rand()%1000)/1000.0-0.5);
    //MatrixOps::multiplyScalar(force,cog,-0.0001);
    //MatrixOps::add(force,force,rando);
    //force = rando -0.001*cog;// sin(t)*Vector3D::UnitX()-cog*((rand()%1000)/1000.0*0.01)+Vector3D::UnitY()*((rand()%1000)/1000.0-0.5)+Vector3D::UnitZ()*((rand()%1000)/1000.0-0.5)+Vector3D::UnitX()*((rand()%1000)/1000.0-0.5);
  });*/

  simulation << da;
  {

    int n(0), m(0), l(0);
    for(int j=0; j < n; j++){
      for(int i=0; i< m; i++){
        for(int k=0; k < l; k++){
          Particle * p = new Particle();
          p->setMass(1);
          p->velocity()(0) = (rand()%1000)/1000.0*1-0.5;
          p->velocity()(1) = (rand()%1000)/1000.0*1-0.5;
          p->velocity()(2) = (rand()%1000)/1000.0*1-0.5;
          p->position()(0) = i*3-m/2*3;
          p->position()(1) = j* 3-n/2*3;
          p->position()(2) = k* 3-n/2*3;

          Sphere * sphere = new Sphere();
          sphere->coordinates().position.mirror(p->position);
          //PointRenderer * pr = new PointRenderer(p->position());
          simulation<< new  SphereRenderer(*sphere);
          simulation<<p;
          //simulation<<pr;
        }
      }
    }
  }
  {


    int n(0), m(2), l(2);
    for(int j=0; j < n; j++){
      for(int i=0; i< m; i++){
        for(int k=0; k < l; k++){
          DynamicBox * p = new DynamicBox();
          
          p->kinematics().velocity()(0) = (rand()%1000)/1000.0*1-0.5;
          p->kinematics().velocity()(1) = (rand()%1000)/1000.0*1-0.5;
          p->kinematics().velocity()(2) = (rand()%1000)/1000.0*1-0.5;
          p->kinematics().angularVelocity()(0) = (rand()%1000)/1000.0*1-0.5;
          p->kinematics().angularVelocity()(1) = (rand()%1000)/1000.0*1-0.5;
          p->kinematics().angularVelocity()(2) = (rand()%1000)/1000.0*1-0.5;
          p->kinematics().position()(0) = i*3-m/2*3;
          p->kinematics().position()(1) = j* 3-n/2*3;
          p->kinematics().position()(2) = k* 3-n/2*3;
          p->kinematics().orientation()(0) = (rand()%1000)/1000.0*1;
          p->kinematics().orientation()(1) = (rand()%1000)/1000.0*1;
          p->kinematics().orientation()(2) = (rand()%1000)/1000.0*1;
          p->kinematics().orientation()(3) = (rand()%1000)/1000.0*1;
          p->kinematics().orientation().normalize();
          // PointRenderer * pr = new PointRenderer(p->position());
          BoxRenderer * br = new BoxRenderer(p->geometry());
          simulation<<p;
          simulation<<br;
        }
      }
    }
  }
  //simulation << new BillboardRenderer();
 simulation << new HistoryModule (setup.defaultSystem.statefulObject(), setup.simulationTimeProvider);

  simulation << new GlutObject(argc,argv);
  
 simulation << new GridRenderer(0);
  simulation << new LightRenderer();
  simulation<<runner;

  
  simulation.initialize();
  runner.run();
  simulation.cleanup();
}
