/*

#include <Dslib>
#include <core/patterns/Singleton.h>

#include <GL/glut.h>


#include <simulation.time/CallbackTask.h>
#include <simulation.time/PeriodicTask.h>


#include <visualization/Color.h>
#include <visualization.opengl/opengl.h>
#include <visualization.opengl.renderer/GridRenderer.h>
#include <visualization.opengl.renderer/LightRenderer.h>
#include <visualization.opengl.renderer/BillboardRenderer.h>
#include <visualization.opengl.renderer.geometry/PolygonRenderer.h>
#include <visualization.opengl.renderer.geometry/BoxRenderer.h>
#include <visualization.opengl.renderer.geometry/PointRenderer.h>
#include <visualization.opengl.renderer.geometry/SphereRenderer.h>


#include <simulation.geometry/primitives/Hexahedron.h>
#include <simulation.geometry/Plane.h>
#include <simulation.geometry/primitives/Sphere.h>

#include <simulation.kinematics/KinematicCoordinates.h>
#include <simulation.history/HistoryModule.h>
#include <simulation.utility/DynamicsAlgorithm.h>

#include <simulation.dynamics/Particle.h>
#include <simulation.dynamics/DynamicBodyModule.h>
#include <simulation.dynamics/RigidBody.h>
#include <simulation.dynamics/primitives/DynamicBox.h>
#include <simulation.dynamics/connection/RigidBodyConnector.h>
#include <simulation.dynamics/connection/ConnectorFactory.h>

#include <simulation.dynamics.force/ForceModule.h>
#include <simulation.dynamics.force/Gravity.h>
#include <simulation.dynamics.force/ForceField.h>

#include <simulation.dynamics.multibody.impulsebased/ImpulseBasedMultiBodyModule.h>
#include <simulation.dynamics.multibody.impulsebased/joints/BallJoint.h>

#include <simulation.model/builder/ModelBuilderBase.h>

#include <utility.reader.urdf/UrdfModelReader.h>

using namespace nspace;
using namespace std;
class GlutObject : public virtual Renderer{
  TYPED_OBJECT(GlutObject);
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


class ConnectorImpulseRenderer : public Renderer{
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
    model.nodes().foreachElement([this](ModelNode * node){
      convertBody(node);
    });
    model.nodes().foreachElement([this](ModelNode * node){
      convertConnector(node);
    });
    model.nodes().foreachElement([this](ModelNode * node){
      convertConnection(node);
    });
    std::cout << model;
  }
    
private:
  void convertConnector(ModelNode * node){
    Connector * connector =0;
    node->get(connector,"connector");
    if(!connector)return;

  }
  void convertConnection(ModelNode * node){
    Connection * connection=0;
    node->get(connection,"connection");
    if(!connection)return;


  }
  void convertBody(ModelNode * node){
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
    //_objects.addComponent(new SphereRenderer(*sphere));
    
    _objects.addComponent(rigidBody);
  }

};



int main(int argc, char** argv){

  DefaultSimulationSetup setup;

  //QtSimulationRunner runner;
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
   
  simulation |= new BallJoint(*c3,*c4);
  simulation |= new BallJoint(*c1,*c2);
  
  simulation |= new ConnectorImpulseRenderer(*c1);
  simulation |= new ConnectorImpulseRenderer(*c2);
  simulation |= new ConnectorImpulseRenderer(*c3);
  simulation |= new ConnectorImpulseRenderer(*c4);
  
  simulation |= b1;
  simulation |= b2;
  simulation |= b3;

  simulation |= c1;
  simulation |= c2;
  simulation |= c3;
  simulation |= c4;


  Hexahedron * box = new Hexahedron(0.5,0.5,0.5);
  box->coordinates().mirror(b1.coordinates());
  simulation |= box;
  simulation |= new BoxRenderer(*box);

  Hexahedron * box2 = new Hexahedron(0.5,0.5,0.5);
  box2->coordinates().mirror(b2.coordinates());
  simulation |= box2;
  simulation |= new BoxRenderer(*box2);

  Hexahedron * box3 = new Hexahedron(0.5,0.5,0.5);
  box3->coordinates().mirror(b3.coordinates());
  simulation |= box3;
  simulation |= box3;
  simulation |= new BoxRenderer(*box3);




  UrdfModelReader & urdfReader = UrdfModelReader::instance();
  
  
  DSLibModelBuilder builder;

  bool result = urdfReader.parseFile(builder,"resources/models/model1.urdf");

  simulation |= builder.simulationObjects();
  

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
  simulation |= new Gravity(1);
  



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


    int n(20), m(4), l(4);
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
          p->kinematics().position()(2) = k* 3-l/2*3;
          p->kinematics().orientation().w() = (rand()%1000)/1000.0*1;
          p->kinematics().orientation().x() = (rand()%1000)/1000.0*1;
          p->kinematics().orientation().y() = (rand()%1000)/1000.0*1;
          p->kinematics().orientation().z() = (rand()%1000)/1000.0*1;
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
 simulation |= new HistoryModule (setup.defaultSystem.statefulObject(), setup.simulationTimeProvider);

  simulation |= new GlutObject(argc,argv);
  
 simulation |= new GridRenderer(0);
  simulation |= new LightRenderer();
  simulation|=runner;

  
  simulation.initialize();
//  runner.run();
  simulation.cleanup();
}
*/
int main(){}
