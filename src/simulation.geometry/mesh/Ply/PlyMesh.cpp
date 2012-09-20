#include "PlyMesh.h"
#include <rply/rply.h>
#include <vector>
using namespace nspace;
using namespace std;


PlyVertex * currentVertex=0;

PlyMesh * getMesh(p_ply_argument argument){
  PlyMesh * mesh;
  long idata;
  ply_get_argument_user_data(argument,(void**)&mesh,&idata);
  return mesh;
}



static int vertexX(p_ply_argument argument) {
  PlyMesh * mesh = getMesh(argument);  
  currentVertex = mesh->addPlyVertex();
  currentVertex->p_ocs(0) =  ply_get_argument_value(argument);  
  return 1;
}
static int vertexY(p_ply_argument argument) {
  currentVertex->p_ocs(1) =  ply_get_argument_value(argument);  
  return 1;
}
static int vertexZ(p_ply_argument argument) {
  currentVertex->p_ocs(2) =  ply_get_argument_value(argument);
  return 1;
}
static int normalX(p_ply_argument argument) {
  currentVertex->normal(0) = ply_get_argument_value(argument);
  return 1;
}
static int normalY(p_ply_argument argument) {  
  currentVertex->normal(1) = ply_get_argument_value(argument);
  return 1;
}
static int normalZ(p_ply_argument argument) {
  currentVertex->normal(2) = ply_get_argument_value(argument);
  return 1;
}

static int faceIndex(p_ply_argument argument) {
  static Index faceIndices[3];
  long length, valueIndex;
  ply_get_argument_property(argument, NULL, &length, &valueIndex);
  double value = ply_get_argument_value(argument);
  if(valueIndex < 0)return 1;
  if(valueIndex > 2)return 1;
  //store three indices in array
  faceIndices[valueIndex] = value;
  //when third index is stored create face
  if(valueIndex==2){    
    PlyMesh * mesh = getMesh(argument);  
    mesh->createFace(faceIndices[0],faceIndices[1],faceIndices[2]);
  }
  return 1;
}

Vertex * PlyMesh::createVertex(){
  return new PlyVertex();
}
void PlyMesh::createFace(Index a, Index b, Index c){
  Vertex * v1 = vertex(a);
  Vertex * v2 = vertex(b);
  Vertex * v3 = vertex(c);

  Edge * e1 = getEdge(v1,v2);
  if(!e1)e1 = addEdge(a,b);
  Edge * e2 = getEdge(v2,v3);
  if(!e2)e2 = addEdge(b,c);
  Edge * e3 = getEdge(v3,v1);
  if(!e3)e3 = addEdge(c,a);
  
  HalfEdge * he1 = e1->getUnconnectedHalfEdge();
  HalfEdge * he2 = e2->getUnconnectedHalfEdge();
  HalfEdge * he3 = e3->getUnconnectedHalfEdge();

  if(! (he1 && he2 && he3))return;

  connect(he1,he2);
  connect(he2,he3);
  connect(he3,he1);
  
  addFace(he1);
}
PlyVertex * PlyMesh::addPlyVertex(){
  return static_cast<PlyVertex*>( addVertex(Vector3D::Zero()) );
}
void PlyMesh::createGeometry(){
  p_ply plyFile = ply_open(filename.c_str(), NULL, 0, NULL);
  if (!plyFile) return;
  if (!ply_read_header(plyFile)) return ;
  
  long vertexCount = ply_set_read_cb(plyFile, "vertex", "x", vertexX, this, 0);
  ply_set_read_cb(plyFile, "vertex", "y", vertexY, this, 0);
  ply_set_read_cb(plyFile, "vertex", "z", vertexZ, this, 0);
  ply_set_read_cb(plyFile, "vertex","nx",normalX, this, 0);
  ply_set_read_cb(plyFile, "vertex","ny",normalY, this, 0);
  ply_set_read_cb(plyFile, "vertex","nz",normalZ, this, 0);

  long faceCount = ply_set_read_cb(plyFile, "face", "vertex_indices", faceIndex, this, 0);
  
  if (!ply_read(plyFile)) return ;
  ply_close(plyFile);

}