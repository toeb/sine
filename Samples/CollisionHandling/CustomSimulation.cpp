#include "CustomSimulation.h"

#include <Visualization/IRenderer.h>
#include <Simulation/Dynamics/Connection/ConnectorFactory.h>
#include <Simulation/Integration/Implementations/ExplicitEuler.h>
#include <Simulation/Integration/Implementations/ImplicitEuler.h>
#include <Simulation/Integration/Implementations/RungeKutta4.h>
#include <Simulation/Integration/Implementations/RungeKuttaFehlberg45.h>
#include <Visualization/Renderers/LightRenderer.h>
#include <Visualization/Renderers/CoordinateSystemRenderer.h>
#include <Visualization/Renderers/CameraRenderer.h>
#include <Visualization/Renderers/SimulationRunnerRenderer.h>
#include <Visualization/Renderers/TextRenderer.h>
#include <Visualization/Renderers/ConnectorRenderer.h>
#include <Visualization/Renderers/ConnectorVelocityRenderer.h>
#include <Visualization/Renderers/ConnectorForceRenderer.h>
#include <Visualization/Renderers/ParticleRenderer.h>
#include <Visualization/Renderers/BoxRenderer.h>
#include <Visualization/Renderers/SpringRenderer.h>
#include <Visualization/Renderers/TweakBar/TweakBarRenderer.h>
#include <Visualization/UserInterface/DelegateAction.h>
#include <Visualization/UserInterface/RealValue.h>
#include <Visualization/Renderers/PlaneRenderer.h>
#include <Visualization/InputHandler.h>
#include <Simulation/SimulationBuilder.h>
#include <Simulation/Textiles/TextileModel.h>
#include <Simulation/DynamicsAlgorithm.h>
#include <Visualization/Renderers/SphereRenderer.h>
#include <Visualization/Renderers/CollisionRenderer.h>
#include <Visualization/Renderers/OctreeRenderer.h>
#include <Simulation/Geometry/Plane.h>
#include <Simulation/Geometry/BoundingVolumes/BoundingSphere.h>
#include <map>
#include <sstream>
#include <Visualization/Renderers/PolygonRenderer.h>
#include <Visualization/UserInterface/Vector3DValue.h>
#include <Simulation/Geometry/Mesh/Ply/PlyMesh.h>
#include <Simulation/Core/Timing/Timer.h>
using namespace IBDS;
using namespace std;

int integratorIndex=0;
vector<SingleStepIntegrator*> integrators;

class DelegateTimer : public Timer{
private:
  std::function<void(Real,Real)> _f;
public:
  DelegateTimer(Time timeoutTime, bool repeat,std::function<void(Real,Real)> f):Timer(timeoutTime,repeat),_f(f)
  {
  }

  void timeout(Time systemTime, Time simulationTime)
  {   
    _f(systemTime,simulationTime);
  }
};

void CustomSimulation::buildModel(){ 
	setName("Collision Handling Example");

	CollisionRenderer *  collisionRenderer =new CollisionRenderer(dynamicsAlgorithm.collisionDetector);
	add(collisionRenderer);
	SimulationBuilder b(*this);  
	Gravity & g = *(b.setGravity(Vector3D(0,-1,0)));
	g.setGravityMagnitude(0.1);
  
  DelegateTimer * timer = new DelegateTimer(1,true,[this](Real sysTime, Real simTime){
    dynamicsAlgorithm.timingModule.printInfo(cout);
    dynamicsAlgorithm.timingModule.resetAccumulatedTimes();
  });
 add(new DelegateAction("activate timer", [timer](){timer->repeat() = !timer->repeat();}));
 add(timer);


  add(&dynamicsAlgorithm.dynamicBodyModule);
  add(&dynamicsAlgorithm.collisionDetector);

  add(new DelegateAction("Render Collisions", [collisionRenderer](){collisionRenderer->renderCollisions()=!collisionRenderer->renderCollisions();}));
	add(new RealValue("Collisiontrace Timeout",collisionRenderer->timeout()));
	add(new DelegateAction("Collisiontrace", [collisionRenderer](){
		collisionRenderer->renderCollisionTrace() = !collisionRenderer->renderCollisionTrace();

		}));

	g.setGravityMagnitude(0.1);
	add( new RealValue("Gravity Magnitude",
		[&g](){return g.getGravityMagnitude();},
		[&g](Real val){g.setGravityMagnitude(val);}));

		{
		auto plane = new DynamicGeometry<Plane>(*new Plane(),0,Matrix3x3::Identity());
		plane->coordinates().position() = Vector3D(0,-4,0);
		plane->coordinates().orientation().setFromAxisAngle(Vector3D(0,0,1),-0.2);
		add(new Vector3DValue("plane ",plane->coordinates().position()));

		add(plane);
		auto renderer = new PlaneRenderer(plane->geometry());
		add(renderer);
		add(new RealValue("plane extent",renderer->extent()));
		add(DynamicCollidable::create(plane->geometry(),plane->body(),0.5,0.01,0.01));
		}

		
		DynamicBox *body = new DynamicBox(1,1,1,1);
		Real planeAngle = -0.2;
		body->coordinates().position().set(0+5*cos(planeAngle)-0.5*sin(planeAngle),-3.99+5*sin(planeAngle)+0.5*cos(planeAngle),0);
		body->coordinates().orientation().setFromAxisAngle(Vector3D(0,0,1),planeAngle);
		add(new BoxRenderer(body->geometry()));
		add(DynamicCollidable::create(*new Octree(body->geometry(),3,* new BoundingSphereFactory()),body->body(),0.5,0.01,0.02));

		body = new DynamicBox(1,1,1,1);
		body->coordinates().position().set(0+10*cos(planeAngle)-0.5*sin(planeAngle),-3.99+10*sin(planeAngle)+0.5*cos(planeAngle),0);
		body->coordinates().orientation().setFromAxisAngle(Vector3D(0,0,1),planeAngle);
		add(new BoxRenderer(body->geometry()));
		add(DynamicCollidable::create(*new Octree(body->geometry(),3,* new BoundingSphereFactory()),body->body(),0.5,0.01,10));

		{
		auto sphere = new DynamicSphere(1,1);
		add(sphere);
		add(new Vector3DValue("sphere",sphere->coordinates().position()));
		add(new SphereRenderer(sphere->geometry()));
		sphere->coordinates().position() = Vector3D(1,-2,0);
		add(DynamicCollidable::create(sphere->geometry(),sphere->body(),0.1,100,50));
		}

		{
		auto box = new DynamicBox();
		add(box);
		add(new Vector3DValue("box", box->coordinates().position()));
		add(new BoxRenderer(box->geometry()));
		box->coordinates().position().set(3,2,0);
		add(DynamicCollidable::create(*new Octree(box->geometry(),3,* new BoundingSphereFactory()),box->body(),0.3,100,50));
		}

		//{
		//auto pyramid = new DynamicGeometry<Pyramid>(*new Pyramid(),1,Matrix3x3::Identity());
		//add(pyramid);
		//add(new Vector3DValue("pyramid",pyramid->coordinates().position()));
		//add(new PolygonRenderer(pyramid->geometry()));
		//pyramid->coordinates().position().set(3,1,0);
		//add(DynamicCollidable::create(*new Octree(pyramid->geometry(),3,* new BoundingSphereFactory()),pyramid->body(),0.3));
		//}

		{
		DynamicSphere * sphere = 0;
		DynamicCollidable * collidable;


		b.setOffset(Vector3D(10,3,4));
		Real radius = 0.5;

		Particle *particle ;
		particle = b.createParticle("p6",Vector3D(-2,-1,0),1);
		sphere = b.createSphere("s6",Vector3D(-2,-1,0),1,radius);
		b.createBallJoint("j6","s6","p6",Vector3D(-2,-1,0));

		add(new SphereRenderer(sphere->geometry()));
		collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
		add(collidable); 

		particle = b.createParticle("p5",Vector3D(-2,0,0),0);
		sphere = b.createSphere("s5",Vector3D(-2,-2,0),2,radius);
		b.createBallJoint("j5","s5","p5",Vector3D(-2,0,0));
		add(new SphereRenderer(sphere->geometry()));
		collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
		add(collidable);

		particle = b.createParticle("p4",Vector3D(-1,0,0),0);
		sphere = b.createSphere("s4",Vector3D(-1,-2,0),2,radius);
		b.createBallJoint("j4","s4","p4",Vector3D(-1,0,0));
		add(new SphereRenderer(sphere->geometry()));
		collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
		add(collidable);

		particle = b.createParticle("p1",Vector3D(0,0,0),0);
		//sphere = b.createSphere("s1",Vector3D(-3,-0.3,0),1,radius);
		sphere = b.createSphere("s1",Vector3D(0,-2,0),2,radius);
		b.createBallJoint("j1","s1","p1",Vector3D(0,0,0));
		add(new SphereRenderer(sphere->geometry()));
		collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
		add(collidable);

		particle = b.createParticle("p2",Vector3D(1,0,0),0);
		sphere= b.createSphere("s2",Vector3D(3,0,0),1,radius);
		b.createBallJoint("j2","s2","p2",Vector3D(1,0,0));
		add(new SphereRenderer(sphere->geometry()));
		collidable = DynamicCollidable::create(sphere->geometry(),sphere->body());
		add(collidable);
		}

		//{
		//for(int i= 0; i < 2; i++){
		//	Particle * p = new Particle();

		//	Sphere * sphere = new Sphere(0.1);
		//	p->position << sphere->coordinates().position;

		//	Vector3D randVector((rand()%1000)/1000.0,(rand()%1000)/1000.0,(rand()%1000)/1000.0);
		//	p->position() = randVector*5+Vector3D(7,0,0);
		//	p->velocity() = randVector*5 - Vector3D(2.5,2.5,2.5);


		//	DynamicCollidable * collidable = DynamicCollidable::create(*sphere,*p);

		//	add(p);
		//	add(sphere);
		//	add(collidable);
		//	add(new SphereRenderer(*sphere));
		//	}
		//}

    {
      Quaternion orientation;
      orientation.setFromAxisAngle(Vector3D(1,0,0),PI /2);
      int clothDim = 20;
      //TextileModel * cloth = TextileModel::createTextileModel(Vector3D(10,0,12),orientation.getMatrix3x3(),200,8,8,clothDim,clothDim);
	  TextileModel * cloth = TextileModel::createTextileModel(Vector3D(10,0,12),orientation.getMatrix3x3(),clothDim*clothDim,clothDim/5,clothDim/5,clothDim,clothDim);
      cloth->setElongationSpringConstant(80);
      cloth->setFlexionSpringConstant(80);
      cloth->setShearSpringConstant(80);

      cloth->getNode(0,0)->particle->setMass(0);
      cloth->getNode(clothDim-1,clothDim-1)->particle->setMass(0);
      cloth->getNode(0,clothDim-1)->particle->setMass(0);
      cloth->getNode(clothDim-1,0)->particle->setMass(0);

      add(cloth);
       for_each(cloth->getSimulationObjects().begin(), cloth->getSimulationObjects().end(), [this](ISimulationObject * obj){
        add(obj);
      });

       cloth->foreachNode([this](TextileNode * node){
         Sphere * sphere = new Sphere(0.1);
         DynamicCollidable * collidable = DynamicCollidable::create(*sphere,*node->particle);
         sphere->coordinates().position.mirror(node->particle->position);
         add(sphere);
         //add(new SphereRenderer(*sphere));
         add(collidable);
       });


       DynamicBox * box = new DynamicBox(90);
       box->kinematics().position() = Vector3D(10,2,12);
       add(box);
       add(new PolygonRenderer(box->geometry()));
       add(DynamicCollidable::create(*new Octree(box->geometry(),3,*new BoundingSphereFactory()),box->body()));
       add(new DelegateAction("box mass",[box](){
         if(box->body().getMass()){
           box->body().setMass(0);
         }else{
           box->body().setMass(1);
         }
       }));
    }

    {
      DynamicGeometry<Rectangle> * rectangle;
      PolygonRenderer * renderer; 
      Real spacing=3;
      DynamicCollidable * collidable;
      Vector3D offset(0,0,-3);
      Vector3D left(-1,0,0);
      Vector3D right(1,0,0);
      Real angle = PI/6;
      Vector3D axis(0,0,1);
      Vector2D rectangleDim(3,2);
      Quaternion q;
      Vector3D pos;
      q.setFromAxisAngle(Vector3D(1,0,0),PI/2);
      for(int i=0; i< 4; i++){
        rectangle =   new DynamicGeometry<Rectangle>(
          *new Rectangle(rectangleDim),
          0,
          Matrix3x3::Zero());
        renderer = new PolygonRenderer(rectangle->geometry());
        collidable = DynamicCollidable::create(*new Octree(rectangle->geometry(),3,*new BoundingSphereFactory()),rectangle->body(),0.1);
        

         pos = offset + Vector3D(0,spacing * i,0);
        Quaternion ori;
        if(i%2){
          pos = pos + right;
          ori.setFromAxisAngle(axis,angle);
        }else{
          pos = pos + left;
          ori.setFromAxisAngle(axis,-angle);
        }

        rectangle->coordinates().position() = pos;
        rectangle->coordinates().orientation() =ori*q;

        add(rectangle);
        add(renderer);
        add(collidable);
      }

      DynamicSphere * sphere = new DynamicSphere(0.1,0.6);
      add(sphere);
      add(new SphereRenderer(sphere->geometry()));
      add(DynamicCollidable::create(sphere->geometry(), sphere->body(),0.4,10,6));
      sphere->coordinates().position() = pos+Vector3D(0,1,0);

    }

    {
      /*
      PlyMesh * mesh = new PlyMesh("cube.ply");
      mesh->initialize();
     // mesh->scale(60,60,60);
      add(mesh);
      PolygonRenderer * r = new PolygonRenderer(*mesh);
     r->drawLabels = false;
     r->drawNormals = false;
      add(r);//*/
    }
		
	}


void CustomSimulation::onSimulationObjectAdded(ISimulationObject * simulationObject){
	Connector * connector = dynamic_cast<Connector*>(simulationObject);
	if(connector){
		add(new ConnectorRenderer(*connector));
		}

	Particle * particle = dynamic_cast<Particle*>(simulationObject);
	if(particle){
		add(new ParticleRenderer(*particle));
		}
	}



void CustomSimulation::buildAlgorithms(){  
	integrators.push_back(new ExplicitEuler(0.01));
	integrators.push_back(new ImplicitEuler(0.02));
	integrators.push_back(new RungeKutta4(0.01));

  
  add(integrators.at(0));
  add(integrators.at(1));
  add(integrators.at(2));

	add(&dynamicsAlgorithm);

	integrator = integrators.at(0);

	integrator->setSystemFunction(dynamicsAlgorithm);


	setIntegrator(*integrator);

	add(new DelegateAction("toggle collision detection",[this](){
		dynamicsAlgorithm.detectCollisions = ! dynamicsAlgorithm.detectCollisions;
		dynamicsAlgorithm.collisionDetector.resetCollisions();
		}));

	add(new DelegateAction("toggle multibody",[this](){
		dynamicsAlgorithm.doMultiBody = ! dynamicsAlgorithm.doMultiBody;
		}));

	add(new RealValue("time", [this](){return time();}, [](Real r){}));
  add(new RealValue("elapsed system time", [this](){return elapsedSystemTime();}, [](Real r){}));
	add(new IntValue("Integrator 0-2 (0=ee, 1=ie,2=rk4)", 
		[this](){
			return integratorIndex;
		},
			[this](int val){
				integratorIndex = val % 3;
				integrator= integrators.at(integratorIndex);
				integrator->setSystemFunction(dynamicsAlgorithm);
				setIntegrator(*integrator);

			}));



		add( new RealValue("Integrator Step Size",
			[this](){return integrator->getStepSize();},
			[this](Real value){integrator->setStepSize(value);}));





		add(new LightRenderer());
		add(new CoordinateSystemRenderer());// renders coordinate system at world origin


		auto cam = new CameraRenderer();
		cam->position() =Vector3D(8,0,30);
		cam->orientation().setFromAxisAngle(Vector3D(0,1,0),PI/2);
		add(cam);

		add(new Vector3DValue("camera position", cam->position()));


	}

