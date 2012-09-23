#pragma once
#include <visualization/IRenderer.h>
#include <visualization.opengl.renderer.geometry/mesh/Mesh.h>

namespace nspace{
  
class MeshRenderer : public IRenderer{
private:
 Mesh & _mesh;
 float _color[4];
public:
  MeshRenderer(Mesh & mesh, const float *  color=0):_mesh(mesh){
    if(color){
      _color[0] = color[0];
      _color[1] = color[1];
      _color[2] = color[2];
      _color[3] = color[3];
    }else{
      _color[0] = 0.6f;
      _color[1] = 0.6f;
      _color[2] = 0.6f;
      _color[3] = 1.0f;
    }
  }
  float * color(){return _color;}
  void render();
protected:
  bool initializeObject();
  void cleanupObject();
};// class MeshRenderer
}