#include <visualization.opengl/opengl.h>
#include "CubeMesh.h"

using namespace nspace;
void CubeMesh::load(){
  Vertex a,b,c,d;

  //leftface
  addVertex(Vector3D(-1,-1,-1), Vector3D(-1,0,0));
  addVertex(Vector3D(-1,-1,1), Vector3D(-1,0,0));
  addVertex(Vector3D(-1,1,1), Vector3D(-1,0,0));
  addVertex(Vector3D(-1,1,-1), Vector3D(-1,0,0));
  addFace(0,1,3);
  addFace(3,1,2);

  //rightface
  addVertex(Vector3D(1,-1,-1), Vector3D(1,0,0));
  addVertex(Vector3D(1,-1,1), Vector3D(1,0,0));
  addVertex(Vector3D(1,1,1), Vector3D(1,0,0));
  addVertex(Vector3D(1,1,-1), Vector3D(1,0,0));

  addFace(4,5,7);
  addFace(7,5,6);

  //topface
  addVertex(Vector3D(-1,1,-1), Vector3D(0,1,0));
  addVertex(Vector3D(-1,1,1), Vector3D(0,1,0));
  addVertex(Vector3D(1, 1,1), Vector3D(0,1,0));
  addVertex(Vector3D(1 ,1,-1), Vector3D(0,1,0));

  addFace(8,9,10);
  addFace(10,8,11);

  //bottomface
  addVertex(Vector3D(-1,-1,-1), Vector3D(0,-1,0));
  addVertex(Vector3D(-1,-1,1), Vector3D(0, -1,0));
  addVertex(Vector3D(1, -1,1), Vector3D(0, -1,0));
  addVertex(Vector3D(1 ,-1,-1), Vector3D(0,-1,0));

  addFace(12,13,14);
  addFace(14,12,15);

  //front
  addVertex(Vector3D(-1,-1,1), Vector3D(0,0,1));
  addVertex(Vector3D( 1,-1,1), Vector3D(0,0,1));
  addVertex(Vector3D( 1, 1,1), Vector3D(0,0,1));
  addVertex(Vector3D(-1, 1,1), Vector3D(0,0,1));

  addFace(16,17,18);
  addFace(18,16,19);

  //back
  addVertex(Vector3D(-1,-1,-1), Vector3D(0,0,-1));
  addVertex(Vector3D( 1,-1,-1), Vector3D(0,0,-1));
  addVertex(Vector3D( 1, 1,-1), Vector3D(0,0,-1));
  addVertex(Vector3D(-1, 1,-1), Vector3D(0,0,-1));

  addFace(20,21,22);
  addFace(22,20,23);
}