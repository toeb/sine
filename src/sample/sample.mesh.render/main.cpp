// base class for sample apps
#include <application.sample.h>
// used to read stanford ply files
#include <utility.reader.ply.h>
// used to read wavefront3d obj files
#include <utility.reader.obj.h>
// needed for BasicMesh/BasicMeshBuilder
#include <simulation.geometry.h>
// needed for BasicMeshRenderer
#include <visualization.opengl.renderer.geometry.h>

using namespace nspace;
using namespace std;

/**
 * \brief My sample. a Simple Sample which rendeers a obj and a ply mesh from the resources/meshes/... directory
 *        
 */
class MySample : public Sample, public virtual PropertyChangingObject, public virtual NamedObject{
  REFLECTABLE_OBJECT(MySample);
public:

  /**
   * \brief Default constructor. (optional)
   */
  MySample(){
    setName("MySample");
  }
  void setup(){
    // create to meshbuilders
    auto builderA = new BasicMeshBuilder();
    auto builderB = new BasicMeshBuilder();

    // create a obj reader and a ply reader
    ObjReader objReader;
    PlyReader plyReader;
    // set the builders
    objReader.setBuilder(builderA);
    plyReader.setBuilder(builderB);
    // read the specified obj and ply files
    if(!objReader.readFile("meshes/obj/airboat.obj"))logError("could not read obj file");
    if(!plyReader.readFile("meshes/ply/bunny.ply"))logError("could not read ply file");
    // create a renderer for first mesh and set its postion to -10 on x axis 
    auto rendererA = new BasicMeshRenderer(*builderA->mesh);
    rendererA->Coordinates().position()= Vector3D(-10,0,0);
    // create a renderer for second mesh and set its position to 10 on x axis, set scaling to 30x
    auto rendererB = new BasicMeshRenderer(*builderB->mesh);
    rendererB->Coordinates().position()=Vector3D(10,0,0);
    rendererB->setScale(Vector3D(30,30,30));
    // add renderers to components (this will pass them to the render engine)
    Components()|=rendererA;
    Components()|=rendererB;
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
