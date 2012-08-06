#include <ds.h>
#include <visualization/glrenderers/general/GridRenderer.h>
#include <visualization/glrenderers/general/LightRenderer.h>
#include <visualization/glrenderers/geometry/PolygonRenderer.h>
#include <simulation/geometry/Primitives/Hexahedron.h>
#include <simulation/kinematics/KinematicBody.h>
#include <visualization/glrenderers/geometry/BoxRenderer.h>
#include <gl/glut.h>
#include <visualization/core/Color.h>
#include <visualization/glrenderers/general/BillboardRenderer.h>
#include <lodepng.h>
#include <simulation/geometry/Plane.h>
#include <simulation/history/HistoryModule.h>
#include <common/patterns/Singleton.h>
#include <math/MatrixOperations.h>
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



int main(int argc, char** argv){
  StaticMatrix<Real,2,4> a;
  StaticMatrix<Real,4,2> b;
  StaticMatrix<Real,2,2> c;
  //setMatrixFunction(a,[](Real &  val, int i, int j){val =  (i+1)*(j+1);});
  //setMatrixFunction(b,[](Real & val, int i, int j){val = (i+1)*(j+1);});
  setMatrixConstant(a, 2);
  setMatrixConstant(b,1);


  MatrixOperations<Real>::MatrixProduct<StaticMatrix<Real,2,2>, StaticMatrix<Real,2,4>,StaticMatrix<Real,4,2> >::multiply(c,a,b);
  
  a.toStream(cout);
  cout << endl;
  b.toStream(cout);
  cout << endl;
  c.toStream(cout);
  cout << endl;

  //return 0;
  DefaultSimulationSetup setup;
  
  cout << DefaultSimulationSetup::Type<<endl;
  cout << Simulation::Type << endl;
  cout << Plane::Type<<endl;
  cout << GlutObject::Type<<endl;
  cout << GridRenderer::Type<<endl;
  cout << IRenderer::Type<<endl;
  QtSimulationRunner runner;
  Simulation simulation;
  int n(40), m(40);
  for(int j=0; j < n; j++){
    for(int i=0; i< m; i++){
      Hexahedron * box = new Hexahedron(2,2,2);
      KinematicBody * body=new KinematicBody();
      body->position()(0) = i*3-m/2*3;
      body->position()(1) = j* 3-n/2*3;
      body->angularVelocity() = Vector3D(0.3,0,0);
      box->coordinates().mirror(*body);
      simulation << body;
      simulation << box;
      simulation << new BoxRenderer(*box);
    }
  }
  simulation << new BillboardRenderer();
  simulation << new HistoryModule (setup.defaultSystem.statefulObject(), setup.simulationTimeProvider);

  simulation << new GlutObject(argc,argv);
  
  simulation << setup;
  simulation << new GridRenderer(0);
  simulation << new LightRenderer();
  simulation<<runner;
  runner.run();
  simulation.cleanup();
}