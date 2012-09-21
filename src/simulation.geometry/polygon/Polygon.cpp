#include "Polygon.h"
#include <simulation.geometry/boundingVolumes/BoundingSphere.h>
#include <algorithm>
#include <math/MathDefs.h>
using namespace nspace;
using namespace std;
using namespace nspace::math::operators;

Classification classifySphere(const BoundingSphere & sphere, const Polygon & polygon){
  const Vector3D & c = sphere.getPositionPCS();
  Real radius = sphere.radius();
  Axis currentAxis;
  Interval a;
    Interval b;
    //check faces
   Classification result = Classification::UNCLASSIFIED;
   for(int i = 0; i < polygon.faces().size(); i++){
    currentAxis.n = polygon.face(i)->n_ocs;
    
    polygon.projectOCS(currentAxis,a);
    Real val = currentAxis.projectOnAxis(c);
    b.a = val - radius;
    b.b = val + radius;

    
    if(a.disjoint(b)){
      return Classification::OUTSIDE;
    }
    if(b.isSubsetOf(a)) {
      result = static_cast<Classification>(result | Classification::INSIDE); 
    }else{
      result = static_cast<Classification>(result | Classification::BOTH); 
    }
  }
   Vector3D dir;
   // check edges
   // [berleg nichmal
   for(int i=0; i < polygon.edges().size(); i++){
     Edge * e = polygon.edge(i);
     e->getDirection(dir);
     currentAxis.n = e->forward->face->n_ocs ^ dir;
     currentAxis.n.normalize();

    polygon.projectOCS(currentAxis,a);
    Real val = currentAxis.projectOnAxis(c);
    b.a = val - radius;
    b.b = val + radius;

    
    if(a.disjoint(b)){
      return Classification::OUTSIDE;
    }
    if(b.isSubsetOf(a)) {
      result = static_cast<Classification>(result | Classification::INSIDE); 
    }else{
      result = static_cast<Classification>(result | Classification::BOTH); 
    }
   }

  return result;
}
Classification classifyBoundingBox(const BoundingBox & aabb, const Polygon & polygon){
  vector<Axis> axes;
  axes.push_back(Axis(Vector3D::UnitX()));
  axes.push_back(Axis(Vector3D::UnitY()));
  axes.push_back(Axis(Vector3D::UnitZ()));
  for(int i = 0; i < polygon.faces().size(); i++){
    axes.push_back(polygon.face(i)->n_ocs);
  }
  for(int i = 0; i < polygon.edges().size(); i++){
    Vector3D edgeDir,e_n;
    polygon.edge(i)->getDirection(edgeDir);
    e_n = edgeDir ^Vector3D::UnitX();
    //Vector3D::crossProduct(edgeDir,Vector3D::UnitX(),e_n);
    e_n.normalize();
    axes.push_back(Axis(e_n));
    
    e_n = edgeDir ^Vector3D::UnitY();
    //Vector3D::crossProduct(edgeDir,Vector3D::UnitY(),e_n);
    e_n.normalize();
    axes.push_back(Axis(e_n));
    
    //Vector3D::crossProduct(edgeDir,Vector3D::UnitZ(),e_n);
    e_n =edgeDir^Vector3D::UnitZ();
    e_n.normalize();
    axes.push_back(Axis(e_n));
  }
  Classification result = Classification::UNCLASSIFIED;
  for(int i = 0 ; i < axes.size(); i++){
    Interval a;
    Interval b;
    polygon.projectOCS(axes[i],a);
    aabb.projectOCS(axes[i],b);
    
    if(a.disjoint(b)){
      return Classification::OUTSIDE;
    }
    if(b.isSubsetOf(a)) {
      result = static_cast<Classification>(result | Classification::INSIDE); 
    }else{
      result = static_cast<Classification>(result | Classification::BOTH); 
    
    }


  }
  return result;
}


Classification Polygon::classify(const BoundingVolume & volume)const{
  const BoundingSphere * sphere = dynamic_cast<const BoundingSphere*>(&volume);
  if(sphere)return classifySphere(*sphere,*this);
  const BoundingBox * aabb = dynamic_cast<const BoundingBox*>(&volume); 
  if(aabb)return classifyBoundingBox(*aabb,*this);
  return UNCLASSIFIED;
}

bool Polygon::initializeObject(){
  createGeometry();
  return correctEdgeDirections();
}

void Polygon::projectOCS(const Axis & axis_ocs, Interval & interval)const{
  interval.setInvalid();

  Vector3D difference;
  for(int i =0; i < vertices().size(); i++){
    //Vector3D::subtract(vertex(i)->p_ocs,axis_ocs.p,difference);
    difference = vertex(i)->p_ocs-axis_ocs.p;
    Real val = axis_ocs.projectOnAxis(difference);
    interval.extendTo(val);

  }
}


bool Polygon::isInsideOCS(const Vector3D & p_ocs)const{
  bool inside = true;
  for(int i=0; i < faces().size(); i++){
    Face * f = face(i);
    Vector3D f_c ;
    f->getCenter(f_c);
    Vector3D p = p_ocs - f_c;
    Real val =1;
    MatrixOps::innerProduct(val,f->n_ocs,p);
    //val = f->n_ocs*p;
    //Vector3D::dotProduct(f->n_ocs,p,val);

    if(val-EPSILON > 0 )return false;
  }
  return true;
}

void Polygon::cleanupObject(){
  deleteGeometry();
}
  
   Real Polygon::calculateBoundingSphereRadius()const{
    Real result = 0;
    for(int i=0; i < vertices().size(); i++){
      Real currentLength = vertices().at(i)->p_ocs.squaredNorm();
      if(result < currentLength)result = currentLength;
    }

    return sqrt(result);
  }

  Vertex * Polygon::createVertex(){
    return new Vertex();
  }
 Vertex * Polygon::addVertex(const Vector3D & p_ocs){
    Vertex * v = createVertex();
    v->index = vertices().size();
    v->p_ocs=p_ocs;
    vertices().push_back(v);
    return v;
  }
  
  Edge * Polygon::addEdge(Index v1, Index v2){
    Edge * e = new Edge();
    e->forward = new HalfEdge();
    e->forward->index = halfEdges().size();
    e->forward->edge = e;
    halfEdges().push_back(e->forward);
    e->backward = new HalfEdge();
    e->backward->index = halfEdges().size();
    e->backward->edge = e;
    halfEdges().push_back(e->backward);

    e->index = edges().size();
    e->A = vertices().at(v1);
    e->B = vertices().at(v2);
    if(!e->A->edge)e->A->edge = e;
    if(!e->B->edge)e->B->edge = e;

    edges().push_back(e);
    return e;
  }
  HalfEdge * Polygon::getHalfEdge(const Vertex * a,const  Vertex * b)const{
    for(int i=0; i < edges().size(); i++){
      Edge * e = edges().at(i);
      if(e->A == a && e->B == b)return e->forward;
      if(e->B == a && e->A == b)return e->backward;

    }
    return 0;
  }
  Edge * Polygon::getEdge(const Vertex * a, const Vertex * b)const{
    for(int i=0; i < edges().size(); i++){
      Edge * e = edges().at(i);
      if(e->A == a  && e->B == b|| e->A == b && e->B==a)return e;
    }
    return 0;
   }

  Face * Polygon::addFace(const vector<Index> & vi){
    
    HalfEdge * e1;
    HalfEdge * e2;
    Vertex * a;
    Vertex * b;
    Vertex * c;
    //iterate through vertex index list
    for(int i = 0; i < vi.size(); i ++){

      a = vertex(vi.at(i));
      b = vertex(vi.at((i+1)%vi.size()));
      c = vertex(vi.at((i+2)%vi.size()));
      // get half edge or create edge (which also creates half edge)
      e1 = getHalfEdge(a,b);
      if(!e1)e1 = addEdge(a->index,b->index)->forward;
      e2 = getHalfEdge(b,c);
      if(!e2)e2 = addEdge(b->index,c->index)->forward;
      //connect the two halfedges 
      connect(e1,e2);      
    }
    //add face
    return addFace(e2);
  }

  
  void Polygon::connect(HalfEdge * e1, HalfEdge * e2){
    if(!e1->next && !e2->previous){
      e1->next = e2;
      e2->previous = e1;
      return;
    }
    if(!e1->previous && !e2->next){
      e2->next = e1;
      e1->previous = e2;
      cout << "had to connect reverse  - i dont think this should happen... who knows"<<endl;
      return;
    }
    cout << "failed to connect half edges" << endl;
  }
  
  Face * Polygon::addFaceSafe(const std::vector<Index> & vertexIndices){
    HalfEdge * e1;
    HalfEdge * e2;
    Vertex * a;
    Vertex * b;
    Vertex * c;
    //todo
    for(int i = 0; i < vertexIndices.size(); i ++){
      a=vertex(vertexIndices.at(i));
      b = vertex(vertexIndices.at((i+1)%vertexIndices.size()));
      c = vertex(vertexIndices.at((i+2)%vertexIndices.size()));
      e1 = getHalfEdge(a,b);
      e2 = getHalfEdge(b,c);
      connect(e1,e2);
    }
    return addFace(e2);
  }

  Face * Polygon::addFace(Index v_1, Index v_2, Index v_3){
    vector<Index> indices;
    indices.push_back(v_1);
    indices.push_back(v_2);
    indices.push_back(v_3);



    return addFace(indices);

  }
  Face * Polygon::addFace(Index v_1, Index v_2, Index v_3, Index v_4){
    vector<Index> indices;
    indices.push_back(v_1);
    indices.push_back(v_2);
    indices.push_back(v_3);
    indices.push_back(v_4);

    return addFace(indices);
  }
  
bool Polygon::correctEdge(HalfEdge * halfEdge){
  //return true;
  if(!halfEdge){
    return false;
  }
  Face * face = halfEdge->face;
  if(face && face->valid)return true;
  if(!halfEdge->next) {
    return false;
  }
  HalfEdge * current = halfEdge->next;
  //cycle through current halfedge cycle
  while(current != halfEdge){
    //if next is not set correctEdgeDirections cannot continue
    if(!current->next){
      return false;
    }
    // if next's next edge is current edge the edge is wrong
    if(current->next->next == current){
      HalfEdge * temp = current->next->next;
      current->next->next = current->next->previous;
      current->next->previous = temp;
    }    
    current = current->next;
  }
  if(!face){
    // if face does not exist it will be created
   // face = addFace(current);
    if(!face)return false;
  }
  //face is valid now 
  face->valid = true;  

  //iterate through all edges
  current = halfEdge->next;
  while(current != halfEdge){
    //call correct edge on every reverse half edge
    HalfEdge * he =  current->getReverseHalfEdge();
    if(!he){
      return false;
    }
    if(!correctEdge(he)){
      return false;
    }

    current = current->next;
  }
  return true;
}

bool Polygon::correctEdgeDirections(){
  if(!halfEdges().size())return true; 
  //reset the valid flag on each face
  for_each(faces().begin(), faces().end(), [](Face * f){
    f->valid = false;
  });
  //get first edge and run correctEdge on it
  HalfEdge * first = halfEdges().at(0);
  return correctEdge(first);
}

void Polygon::scale(Real x, Real y, Real z){
  Matrix3x3 mat = Matrix3x3::Zero();
  mat(0,0)=x;
  mat(1,1)=y;
  mat(2,2)=z;

  for_each(vertices().begin(), vertices().end(), [&mat](Vertex * v){
    v->p_ocs = mat * v->p_ocs ;
  });

}

  Face *  Polygon::addFace(HalfEdge * listHead ){
    int numberOfEdges=0;
    HalfEdge * current = listHead;
    Edge * e1=0;
    Edge * e2=0;

    // checks if listhead is part of a face with at least three half edges
    while(true){
      if(current == 0)return 0;
      numberOfEdges++;
      if(!e1)e1 = current->edge;
      else if(!e2) e2 = current->edge;
      current = current->next;
      if(current == listHead)break;
    }
    if(numberOfEdges<3)return 0;

    //create face 
    Face * f = new Face();
    f->index = faces().size();
    f->vertexCount = numberOfEdges;
    f->first=listHead;
    current = listHead;

    //set the face of all half edges    
    while(true){
      current->face=f;
      current = current ->next;
      if(current==listHead)break;
    }

    // calculate the normal of the face by creating the crossproduct between edge one and edge 2
    Vector3D a,b;    
    e1->getDirection(a);
    e2->getDirection(b);        
    //Vector3D::crossProduct(a,b,f->n_ocs);
    f->n_ocs = a^b;
    f->n_ocs.normalize();

    //add edge
    faces().push_back(f);

    //return face
    return f;
  }
  inline Vertex * Polygon::vertex(Index i){
    return _vertices.at(i);
  }
  inline Edge * Polygon::edge(Index i){
    return _edges.at(i);
  }
  inline Face * Polygon::face(Index i){
    return _faces.at(i);
  }
  inline HalfEdge * Polygon::halfEdge(Index i){
    return _halfEdges.at(i);
  }
  
  inline Vertex * Polygon::vertex(Index i)const{
    return _vertices.at(i);
  }
  inline Edge * Polygon::edge(Index i)const{
    return _edges.at(i);
  }
  inline Face * Polygon::face(Index i)const{
    return _faces.at(i);
  }
  inline HalfEdge * Polygon::halfEdge(Index i)const{
    return _halfEdges.at(i);
  }

  void Polygon::deleteGeometry(){
    for(int i = 0; i < vertices().size(); i++){
      delete vertices().at(i);  
    }
    for(int i = 0; i < edges().size(); i++){
      delete edges().at(i);  
    }
    for(int i = 0; i < faces().size(); i++){
      delete faces().at(i);  
    }
    for(int i = 0; i < halfEdges().size(); i++){
      delete halfEdges().at(i);  
    }
    halfEdges().clear();
    vertices().clear();
    edges().clear();
    faces().clear();
  };
  vector<HalfEdge*> & Polygon::halfEdges(){return _halfEdges;}
  vector<Face*> & Polygon::faces(){return _faces;}
  vector<Edge*> & Polygon::edges(){return _edges;}
  vector<Vertex*> & Polygon::vertices(){return _vertices;}
  
  const vector<Face*> & Polygon::faces()const{return _faces;};
  const vector<Edge*> & Polygon::edges()const{return _edges;};
  const vector<Vertex*> & Polygon::vertices()const{return _vertices;};
  const vector<HalfEdge*> & Polygon::halfEdges()const{
    return _halfEdges;
  }
