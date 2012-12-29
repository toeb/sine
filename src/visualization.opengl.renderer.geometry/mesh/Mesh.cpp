#include "Mesh.h"

#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>

#include <visualization.opengl/MiniGL.h>
#include <algorithm>
using namespace nspace;

void Mesh::normalize(){
  Real maxDistance = 0;
  foreachVertex([&maxDistance](Vertex * v){
    for(int i=0; i < 3; i++){
      if(maxDistance < v->position(i))maxDistance = v->position(i);
    }
  });
  if(maxDistance==0)return;
  foreachVertex([&maxDistance](Vertex * v){
    v->position = v->position * (1.0/maxDistance);
  });
}

bool Mesh::initializeObject(){
  load();
  normalize();
  return true;
}

/**
* \brief Destroys this object.
*
* \author Tobias Becker
* \date 05.04.2012
*/
void Mesh::cleanupObject(){
}

void Mesh::foreachVertex(std::function<void (Vertex *)> f){
  for_each(_vertices.begin(), _vertices.end(), f);
}
void Mesh::foreachFace(std::function<void (Face*)> f){
  for_each(_faces.begin(), _faces.end(), f);
}

Vertex* Mesh::addVertex(Vertex * vertex){
  vertex->id = _vertices.size();
  _vertices.push_back(vertex);
  return vertex;
}
Vertex* Mesh::addVertex(const Vector3D & position, const Vector3D & normal){
  Vertex * vertex = new Vertex();
  vertex->normal = normal;
  vertex->position = position;
  return addVertex(vertex);
}
Vertex * Mesh::addVertex(const Vector3D & position){
  Vertex * vertex = new Vertex;
  vertex->position = position;
  return addVertex(vertex);
}
Face* Mesh::addFace(Index a, Index b, Index c){
  return addFace(vertex(a), vertex(b),vertex(c));
}

Face* Mesh::addFace(Vertex *a, Vertex* b, Vertex *c){
  Face * face = new Face();
  face->vertices.push_back(a);
  face->vertices.push_back(b);
  face->vertices.push_back(c);
  return addFace(face);
}
Face* Mesh::addFace(Face * face){
  face->id = _faces.size();
  _faces.push_back(face);
  return face;
}

Face * Mesh::face(Index i){
  if(! (i < _faces.size()) )return 0;
  return _faces[i];
}
Vertex * Mesh::vertex(Index i){
  if(! (i < _vertices.size()) )return 0;
  return _vertices[i];
}
/*
struct vertex_struct{
float x, y, z;
float nx,ny,nz;
float u,v;
float r,g,b, a;
};

///< Number of faces, indices and vertices
GLsizei faceCount,indexCount,vertexCount;
///< Buffer for vertex data
GLuint vertexBuffer;
///< Buffer for index data
GLuint indexBuffer;
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(i) ((char*)NULL + (i))
#endif
using namespace mbslib;

Mesh::Mesh(){
vertexBuffer=0;
indexBuffer=0;
}

bool Mesh::initializeObject(){
if(glewInit()!=GLEW_OK )return false;
vertex_struct* vertices=0;
unsigned int * indices=0;

load(&vertices,&indices,&vertexCount,&faceCount,&indexCount);

if(!vertices)return false;
if(!indices)return false;

glGenBuffers(1,&vertexBuffer);
glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof (struct vertex_struct) * vertexCount, vertices, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);

glGenBuffers(1, &indexBuffer);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices[0]) * faceCount * 3, indices, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

return true;
}
void mbslib::Mesh::cleanupObject(){}

void mbslib::Mesh::render(){
if(!vertexBuffer)return;
if(!indexBuffer)return;

//glFrontFace(GL_CCW);
glBindBufferARB(GL_ARRAY_BUFFER, vertexBuffer);
glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3, GL_FLOAT, sizeof (struct vertex_struct), BUFFER_OFFSET(0));

glEnableClientState(GL_NORMAL_ARRAY);
glNormalPointer(GL_FLOAT, sizeof (struct vertex_struct), BUFFER_OFFSET(3 * sizeof (float)));

glEnableClientState(GL_TEXTURE_COORD_ARRAY);
glTexCoordPointer(2, GL_FLOAT, sizeof (struct vertex_struct), BUFFER_OFFSET(6 * sizeof(float)));

glDrawElements(GL_TRIANGLES, faceCount * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

glDisableClientState(GL_TEXTURE_COORD_ARRAY);
glDisableClientState(GL_NORMAL_ARRAY);
glDisableClientState(GL_VERTEX_ARRAY);
}
*/