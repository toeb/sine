#include "Polygon.h"


using namespace IBDS;
using namespace std;


Classification Polygon::classify(const Vector3D & c, Real radius)const{
  vector<Axis> axes;
   for(int i = 0; i < faces().size(); i++){
    axes.push_back(Axis(face(i)->n_ocs));
  }

   Classification result = Classification::UNCLASSIFIED;
  for(int i = 0 ; i < axes.size(); i++){
    Interval a;
    Interval b;
    projectOCS(axes[i],a);
    Real val = axes[i].projectOnAxis(c);
    b.a = val - radius;
    b.b = val + radius;

    
    if(a.disjoint(b)){
      return Classification::OUTSIDE;
    }
    if(b.subsetOf(a)) {
      result = static_cast<Classification>(result | Classification::INSIDE); 
    }else{
      result = static_cast<Classification>(result | Classification::BOTH); 
    }


  }
  return result;
}

Classification Polygon::classify(const AABB & aabb)const{
  vector<Axis> axes;
  axes.push_back(Axis(Vector3D::e1()));
  axes.push_back(Axis(Vector3D::e2()));
  axes.push_back(Axis(Vector3D::e3()));
  for(int i = 0; i < faces().size(); i++){
    axes.push_back(face(i)->n_ocs);
  }
  for(int i = 0; i < edges().size(); i++){
    Vector3D edgeDir,e_n;
    edge(i)->getDirection(edgeDir);
    Vector3D::crossProduct(edgeDir,Vector3D::e1(),e_n);
    e_n.normalize();
    axes.push_back(Axis(e_n));
    
    Vector3D::crossProduct(edgeDir,Vector3D::e2(),e_n);
    e_n.normalize();
    axes.push_back(Axis(e_n));
    
    Vector3D::crossProduct(edgeDir,Vector3D::e3(),e_n);
    e_n.normalize();
    axes.push_back(Axis(e_n));
  }
  Classification result = Classification::UNCLASSIFIED;
  for(int i = 0 ; i < axes.size(); i++){
    Interval a;
    Interval b;
    projectOCS(axes[i],a);
    aabb.projectOCS(axes[i],b);
    
    if(a.disjoint(b)){
      return Classification::OUTSIDE;
    }
    if(b.subsetOf(a)) {
      result = static_cast<Classification>(result | Classification::INSIDE); 
    }else{
      result = static_cast<Classification>(result | Classification::BOTH); 
    
    }


  }
  return result;
}

bool Polygon::initializeObject(){
  createGeometry();
  return true;
}
void Polygon::projectOCS(const Axis & axis_ocs, Interval & interval)const{
  interval.setInvalid();

  
  for(int i =0; i < vertices().size(); i++){
    Real val = axis_ocs.projectOnAxis(vertex(i)->p_ocs-axis_ocs.p);
    if(interval.a>val)interval.a = val;
    if(interval.b<val)interval.b = val;

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
    Vector3D::dotProduct(f->n_ocs,p,val);
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
      Real currentLength = vertices().at(i)->p_ocs.length2();
      if(result < currentLength)result = currentLength;
    }

    return sqrt(result);
  }

 Vertex * Polygon::addVertex(const Vector3D & p_ocs){
    Vertex * v = new Vertex();
    v->index = vertices().size();
    v->p_ocs.assign(p_ocs);
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
  }
  Face * Polygon::addFace(const vector<Index> & vi){
    
    HalfEdge * e1;
    HalfEdge * e2;
    Vertex * a;
    Vertex * b;
    Vertex * c;
    for(int i = 0; i < vi.size(); i ++){
      a=vertex(vi.at(i));
      b = vertex(vi.at((i+1)%vi.size()));
      c = vertex(vi.at((i+2)%vi.size()));
      e1 = getHalfEdge(a,b);
      e2 = getHalfEdge(b,c);
      e1->next = e2; 
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
  

  Face *  Polygon::addFace(HalfEdge * listHead ){
    int numberOfEdges=0;
    HalfEdge * current = listHead;
    Edge * e1=0;
    Edge * e2=0;
    while(true){
      if(current == 0)return 0;
      numberOfEdges++;
      if(!e1)e1 = current->edge;
      else if(!e2) e2 = current->edge;
      current = current->next;
      if(current == listHead)break;
    }
    if(numberOfEdges<3)return 0;

    Face * f = new Face();
    f->index = faces().size();
    f->vertexCount = numberOfEdges;
    f->first=listHead;
    current = listHead;
    while(true){
      current->face=f;
      current = current ->next;
      if(current==listHead)break;
    }

    Vector3D a,b;
    
    e1->getDirection(a);
    e2->getDirection(b);
    

    Vector3D::crossProduct(a,b,f->n_ocs);
    f->n_ocs.normalize();
   // if(listHead->edge->BA == listHead)Vector3D::multiplyScalar(-1,f->n_ocs,f->n_ocs);


    faces().push_back(f);
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
