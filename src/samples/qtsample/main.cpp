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
#include <lodepng.h>
#include <simulation/geometry/Plane.h>
#include <simulation/history/HistoryModule.h>
#include <common/patterns/Singleton.h>
//#include <math/MatrixOperations.h>
#include <simulation/force/ForceField.h>
#include <simulation/dynamics/Particle.h>
#include <visualization/glrenderers/geometry/PointRenderer.h>
#include <simulation/dynamics/DynamicBodyModule.h>
#include <simulation/force/ForceModule.h>
#include <simulation/utility/DynamicsAlgorithm.h>
#include <simulation/force/Gravity.h>
#include <simulation/dynamics/RigidBody.h>
#include <simulation/dynamics/primitives/DynamicBox.h>
#include <math/matrix2/StaticMatrix.h>
#include <math/MatrixOperations.h>
#include <math/matrix2/StaticMatrixOperators.h>
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


template<typename T, int n1=10000000>
class MatrixPerformanceTests{
public:
  void runSuite(){
    std::cout << "StackInit " << stackInitializePerformance() << " s" <<endl;
    std::cout << "HeapInit " << stackInitializePerformance() << " s" <<endl;
    std::cout << "HeapInitDelete " << stackInitializePerformance() << " s" <<endl;
    std::cout << "MatrixMult " << stackInitializePerformance() << " s" <<endl;
  }
Time stackInitializePerformance(){
  Time start= systemTime();
  for(int i=0; i < n1; i++)
    T t;  
  Time end=systemTime();
  return end-start;
};
Time heapInitializePerformance(){
  Time start= systemTime();
  for(int i=0; i < n1; i++)
    new T;  
  Time end=systemTime();
  return end-start;
};
Time heapDeletePerformance(){
  
  Time start= systemTime();
  for(int i=0; i < n1; i++)
  {delete new T;}  

  Time end=systemTime();
  return end-start;
};
Time matrixMultTest(){
  T a;
  a.setZero();
  T b;
  b.setZero();
  Time start= systemTime();
  for(int i=0; i < n1; i++)
  {a*b;}  

  Time end=systemTime();
  return end-start;
};
};
using namespace matrix2;
int main(int argc, char** argv){
 /* MatrixPerformanceTests<Matrix3x3> suiteA;
  suiteA.runSuite();
  MatrixPerformanceTests<StaticMatrix<Real,3,3> >suiteB;
  suiteB.runSuite();
  return 0;
  matrix2::StaticMatrix<Real,3,3> mat33;
  matrix2::StaticMatrix<Real,3,4> mat34;
  mat34.setZero();
  mat33.setZero();
  cout << mat34;
  cout <<mat33;

  MatrixOperations<Real>::setConstant(mat34,1);
  cout << mat34;
  MatrixOperations<Real>::setFunction(mat33,[](Real & a,int i, int k){a=i==k;});
  cout <<mat33;

  MatrixOperations<Real>::addition(mat33,mat33,mat33);
  cout <<mat33;

  mat33 = mat33+mat33;
  cout <<mat33;

  mat33 = mat33*mat33;
  cout <<mat33;

  auto a =mat33*mat34;
  cout <<a;

  auto d = a * 0.3;
  cout <<d;
  return 0;

  //return 0;*/
  DefaultSimulationSetup setup;

  QtSimulationRunner runner;
  Simulation simulation;
  {

  int n(0), m(0), l(0);
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
  // simulation << new Gravity(1);
  simulation << new ForceField([](Vector3D & force, Vector3D & torque, const Vector3D & cog, Time t){
    Vector3D rando ((rand()%1000)/1000.0-0.5,(rand()%1000)/1000.0-0.5,(rand()%1000)/1000.0-0.5);
    force = rando -0.001*cog;// sin(t)*Vector3D::UnitX()-cog*((rand()%1000)/1000.0*0.01)+Vector3D::UnitY()*((rand()%1000)/1000.0-0.5)+Vector3D::UnitZ()*((rand()%1000)/1000.0-0.5)+Vector3D::UnitX()*((rand()%1000)/1000.0-0.5);
  });
  simulation << da;
  {

    int n(0), m(0), l(0);
    for(int j=0; j < n; j++){
      for(int i=0; i< m; i++){
        for(int k=0; k < l; k++){
          Particle * p = new Particle();
          p->setMass(1);
          p->velocity()(0) = (rand()%1000)/1000.0*1;
          p->velocity()(1) = (rand()%1000)/1000.0*1;
          p->velocity()(2) = (rand()%1000)/1000.0*1;
          p->position()(0) = i*3-m/2*3;
          p->position()(1) = j* 3-n/2*3;
          p->position()(2) = k* 3-n/2*3;
          
          PointRenderer * pr = new PointRenderer(p->position());

          simulation<<p;
          simulation<<pr;
        }
      }
    }
  }
  {


    int n(25), m(25), l(25);
    for(int j=0; j < n; j++){
      for(int i=0; i< m; i++){
        for(int k=0; k < l; k++){
          DynamicBox * p = new DynamicBox();
          
          p->kinematics().velocity()(0) = (rand()%1000)/1000.0*1;
          p->kinematics().velocity()(1) = (rand()%1000)/1000.0*1;
          p->kinematics().velocity()(2) = (rand()%1000)/1000.0*1;
          p->kinematics().angularVelocity()(0) = (rand()%1000)/1000.0*1;
          p->kinematics().angularVelocity()(1) = (rand()%1000)/1000.0*1;
          p->kinematics().angularVelocity()(2) = (rand()%1000)/1000.0*1;
          p->kinematics().position()(0) = i*3-m/2*3;
          p->kinematics().position()(1) = j* 3-n/2*3;
          p->kinematics().position()(2) = k* 3-n/2*3;

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
  
 simulation << setup;
 simulation << new GridRenderer(0);
  simulation << new LightRenderer();
  simulation<<runner;

  
  simulation.initialize();
  runner.run();
  simulation.cleanup();
}
