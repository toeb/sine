#include "BasicMeshBuilder.h"

using namespace nspace;
using namespace std;



void BasicMeshBuilder::position(Vector3D && position){
  vertices.push(position);
}

void BasicMeshBuilder::face(FaceType && face){
  // ignore all faces except default face group 0
  //if(face.group)return;
  faces.push(face);
};

void BasicMeshBuilder::end(){
  mesh = std::shared_ptr<BasicMesh>(new BasicMesh(vertices.size(),faces.size()));

  Index faceIndex=0;
  Index vertexIndex=0;

  while(vertices.size()){
    mesh->vertices[vertexIndex]=vertices.front();
    vertices.pop();
    vertexIndex++;
  }

  while(faces.size()){
    for(auto vertex : faces.front()){        
      mesh->faces[faceIndex].push_back(vertex.position-1);
    }
    faces.pop();
    faceIndex++;
  }
}