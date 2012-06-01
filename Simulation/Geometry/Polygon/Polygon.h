#pragma once

#include <Simulation/Geometry/Geometry.h>
#include <Simulation/Geometry/Polygon/Vertex.h>
#include <Simulation/Geometry/Polygon/HalfEdge.h>
#include <Simulation/Geometry/Polygon/Edge.h>
#include <Simulation/Geometry/Polygon/Face.h>

#include <vector>


namespace IBDS{

class Polygon : public Geometry{
private:
  // a polygon consiste of faces, edges, half edges and vertices
  std::vector<Face*> _faces;
  std::vector<Edge*> _edges;
  std::vector<HalfEdge*> _halfEdges;
  std::vector<Vertex*> _vertices;
public:
  static const TypeId type;
  const TypeId getType()const;
  Classification classify(const BoundingVolume & volume)const;
  
  

  const std::vector<HalfEdge*> & halfEdges() const;
  const std::vector<Face*> & faces() const;
  const std::vector<Edge*> & edges() const;
  const std::vector<Vertex*> & vertices()const;
  
  std::vector<HalfEdge*> & halfEdges();
  std::vector<Face*> & faces();
  std::vector<Edge*> & edges();
  std::vector<Vertex*> & vertices();
  
  
  inline Vertex * vertex(Index i);
  inline Edge * edge(Index i);
  inline Face * face(Index i);
  inline HalfEdge * halfEdge(Index i);
  inline Vertex * vertex(Index i)const;
  inline Edge * edge(Index i)const;
  inline Face * face(Index i)const;
  inline HalfEdge * halfEdge(Index i)const;

  bool isInsideOCS(const Vector3D & p_ocs)const;
  virtual Real calculateBoundingSphereRadius()const;

  void projectOCS(const Axis & axis_ocs, Interval & result)const; 
protected:
  // some utility methods
  HalfEdge * getHalfEdge(const Vertex * a, const Vertex  *b)const;
  Vertex * addVertex(const Vector3D & p_ocs);
  Edge * addEdge(Index v_i, Index v_j);


  Face *  addFace(HalfEdge * listHead );
  Face * addFace(Index v_1, Index v_2, Index v_3);
  Face * addFace(Index v_1, Index v_2, Index v_3, Index v_4);
  Face * addFace(const std::vector<Index> & vertexIndices);


  virtual void createGeometry(){};
  void deleteGeometry();

  virtual bool initializeObject();
  virtual void cleanupObject();
private:


};
}