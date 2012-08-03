#include <ds.h>
#include <visualization/glrenderers/general/GridRenderer.h>
#include <visualization/glrenderers/general/LightRenderer.h>
#include <visualization/glrenderers/geometry/PolygonRenderer.h>
#include <simulation/geometry/Primitives/Hexahedron.h>
#include <gl/glut.h>
using namespace nspace;
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