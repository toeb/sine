#include "PlyMesh.h"

#include <rply/rply.h>
#include <vector>

using namespace nspace;

using namespace std;

PlyMesh * getMesh(p_ply_argument argument){
  void * data;
  long idata;
  ply_get_argument_user_data(argument, &data,&idata);
  PlyMesh * mesh = reinterpret_cast<PlyMesh*>(data);
  return mesh;
}
static int vertexXCallback(p_ply_argument argument) {  
  PlyMesh * mesh = getMesh(argument); 
  mesh->currentVertex()->position(0) = ply_get_argument_value(argument);
  return 1;
}
static int vertexYCallback(p_ply_argument argument) {
  PlyMesh * mesh = getMesh(argument); 
  mesh->currentVertex()->position(1) = ply_get_argument_value(argument);
  return 1;
}
static int vertexZCallback(p_ply_argument argument) {
  PlyMesh * mesh = getMesh(argument); 
  mesh->currentVertex()->position(2) = ply_get_argument_value(argument);
  return 1;

}
static int vertexNXCallback(p_ply_argument argument) {
  PlyMesh * mesh = getMesh(argument); 
  mesh->currentVertex()->normal(0) = ply_get_argument_value(argument);
  return 1;
}
static int vertexNYCallback(p_ply_argument argument) {
  PlyMesh * mesh = getMesh(argument); 
  mesh->currentVertex()->normal(1) = ply_get_argument_value(argument);
  return 1;
}
static int vertexNZCallback(p_ply_argument argument) {
  PlyMesh * mesh = getMesh(argument); 
  mesh->currentVertex()->normal(2) = ply_get_argument_value(argument);
  mesh->nextVertex();
  return 1;
}

static int faceCallback(p_ply_argument argument) {
  
  PlyMesh * mesh = getMesh(argument); 
  long length, valueIndex;
  ply_get_argument_property(argument, NULL, &length, &valueIndex);
  double value = ply_get_argument_value(argument);
  if(valueIndex < 0)return 1;
  if(valueIndex > 2)return 1;

  Vertex * vertex = mesh->vertex((Index)value);
  if(!vertex){
    cout << "oho"<<endl;
  }
  mesh->currentFace()->vertices.push_back(vertex);
  if(valueIndex==2){
    mesh->nextFace();
  }
  return 1;
}

void PlyMesh::nextFace(){
  if(_currentFace)addFace(_currentFace);
  _currentFace = new Face();
}
void PlyMesh::nextVertex(){
  if(_currentVertex) addVertex(_currentVertex);
  _currentVertex = new Vertex();
}
void PlyMesh::load(){
  
  p_ply ply = ply_open(filename.c_str(), NULL, 0, NULL);
  if (!ply) return;
  if (!ply_read_header(ply)) return ;
  
  /*long vertexCount =*/ ply_set_read_cb(ply, "vertex", "x", vertexXCallback, this, 0);

  ply_set_read_cb(ply, "vertex", "y", vertexYCallback, this, 0);
  ply_set_read_cb(ply, "vertex", "z", vertexZCallback, this, 0);
  ply_set_read_cb(ply, "vertex","nx",vertexNXCallback,this,0);
  ply_set_read_cb(ply, "vertex","ny",vertexNYCallback,this,0);
  ply_set_read_cb(ply, "vertex","nz",vertexNZCallback,this,0);
  /*long faceCount = */ply_set_read_cb(ply, "face", "vertex_indices", faceCallback, this, 0);
  
  if (!ply_read(ply)) return ;
  ply_close(ply);
}
