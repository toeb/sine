#include "BasicMesh.h"


using namespace nspace;
using namespace std;

BasicMesh::BasicMesh(uint nverts,uint nfaces) : nVerts(nverts),nFaces(nfaces){
  vertices=new Vector3D[nverts];
  faces = new std::vector<unsigned int>[nfaces];
}
BasicMesh::~BasicMesh(){
  delete[] vertices;
  delete[] faces;
  vertices=0;
  faces=0;
}