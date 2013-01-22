#include "BasicMeshRenderer.h"

#include <visualization.opengl.h>
using namespace nspace;
using namespace std;


BasicMeshRenderer::BasicMeshRenderer(BasicMesh & mesh):_mesh(mesh){
  setColor("blue");
  setScale(Vector3D(1,1,1));
  Coordinates() = Coordinates().identity();
}
void BasicMeshRenderer::render(){
  glPushAll();
  glColor(_Color);
  glTransformation(_Coordinates);
  glScale(_Scale);  
  for(int i=0; i < _mesh.nFaces;i++){
    const auto & face=_mesh.faces[i];
    switch(face.size()){
    case 3:{
      auto a = _mesh.vertices[face[0]];
      auto b = _mesh.vertices[face[1]];
      auto c = _mesh.vertices[face[2]];
      glTriangle(a,b,c);
      break;
           }
    case 4:{

      auto a = _mesh.vertices[face[0]];
      auto b = _mesh.vertices[face[1]];
      auto c = _mesh.vertices[face[2]];
      auto d = _mesh.vertices[face[3]];
      glQuad(a,b,c,d);

      break;
           }
    case 1:
    case 2:
      break;
    default:

      glBegin(GL_TRIANGLE_FAN);

      for(int j=0; j < face.size(); j++){
        glVertex(_mesh.vertices[face[j]]);
      }
      glEnd();

      //logInfo("cannot render faces with "<<_mesh.faces[i].size()<<" vertices ");
      break;
    }
  }
  glPopAll();
}