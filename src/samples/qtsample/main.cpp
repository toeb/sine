#include <ds.h>
#include <visualization/glrenderers/general/GridRenderer.h>
#include <visualization/glrenderers/general/LightRenderer.h>
#include <visualization/glrenderers/geometry/PolygonRenderer.h>
#include <simulation/geometry/Primitives/Hexahedron.h>
#include <simulation/kinematics/KinematicBody.h>
#include <gl/glut.h>
#include <visualization/core/Color.h>
using namespace nspace;
using namespace std;
class GlutObject : public IRenderer{
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
  DefaultSimulationSetup setup;
  QtSimulationRunner runner;
  Simulation simulation;

  Hexahedron box(2,2,2);

  KinematicBody body;
  //body.angularVelocity() = Vector3D(0.3,0,0);
  box.coordinates().mirror(body);

  cout << Color::loadColors("resources/colors/palette.txt") << " colors loaded "<<endl;
  if(Color::getColorByName("AliceBlue")!=Color::unknown)cout << Color::getColorByName("AliceBlue") <<endl;


  simulation << body;

  simulation << box;
  simulation << new GlutObject(argc,argv);
  PolygonRenderer polygonRenderer(box);
  simulation << polygonRenderer;
  
  simulation << setup;
  simulation << new GridRenderer(0);
  simulation << new LightRenderer();
  simulation<<runner;
  runner.run();
}