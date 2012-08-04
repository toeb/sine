#include <ds.h>
#include <visualization/glrenderers/general/GridRenderer.h>
#include <visualization/glrenderers/general/LightRenderer.h>
#include <visualization/glrenderers/geometry/PolygonRenderer.h>
#include <simulation/geometry/Primitives/Hexahedron.h>
#include <simulation/kinematics/KinematicBody.h>
#include <visualization/glrenderers/geometry/BoxRenderer.h>
#include <gl/glut.h>
#include <visualization/core/Color.h>
#include <lodepng.h>
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

class Image : public virtual ISimulationObject{
private:
  vector<unsigned char> _imageBuffer;
  vector<unsigned char> _image;
  lodepng::State _state;
  unsigned int _width;
  unsigned int _height;
protected:
  bool initializeObject(){
    lodepng::load_file(_imageBuffer,"resources/images/testimage.png");
    unsigned int error = lodepng::decode(_image,_width,_height,_state,_imageBuffer);
    
    return true;
  }
  void cleanupObject(){

  }
};

int main(int argc, char** argv){
  DefaultSimulationSetup setup;
  QtSimulationRunner runner;
  Simulation simulation;
  int n(5), m(5);
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

  simulation << new Image();
  simulation << new GlutObject(argc,argv);
  
  simulation << setup;
  simulation << new GridRenderer(0);
  simulation << new LightRenderer();
  simulation<<runner;
  runner.run();
  simulation.cleanup();
}