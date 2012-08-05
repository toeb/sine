#pragma once

#include <simulation/geometry/Geometry.h>
#include <simulation/geometry/polygon/Vertex.h>
#include <simulation/geometry/polygon/HalfEdge.h>
#include <simulation/geometry/polygon/Edge.h>
#include <simulation/geometry/polygon/Face.h>

#include <vector>


namespace nspace{

class Polygon : public Geometry{
  TYPED_OBJECT;
private:
  // a polygon consist of faces, edges, half edges and vertices
  std::vector<Face*> _faces;
  std::vector<Edge*> _edges;
  std::vector<HalfEdge*> _halfEdges;
  std::vector<Vertex*> _vertices;
public:

  /**
   * \brief Scales all vertices
   *
   * 
   *
   * \param x The x coordinate.
   * \param y The y coordinate.
   * \param z The z coordinate.
   */
  void scale(Real x, Real y, Real z);



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

  /**
   * \brief corrects the halfedge cycles (not working correctly currently)
   *
   * 
   *
   * \return true if it succeeds, false if it fails.
   */
  bool correctEdgeDirections();

  virtual Vertex * createVertex();
  
  
  // some utility methods
  HalfEdge * getHalfEdge(const Vertex * a, const Vertex  *b)const;
  Edge * getEdge(const Vertex * a, const Vertex * b)const;
  Vertex * addVertex(const Vector3D & p_ocs);
  Edge * addEdge(Index v_i, Index v_j);

  void connect(HalfEdge * e1, HalfEdge * e2);
  Face *  addFace(HalfEdge * listHead );
  Face * addFace(Index v_1, Index v_2, Index v_3);
  Face * addFace(Index v_1, Index v_2, Index v_3, Index v_4);
  Face * addFace(const std::vector<Index> & vertexIndices);
  Face * addFaceSafe(const std::vector<Index> & vertexIndices);

  /**
   * \brief Creates the geometry subclasses override this method to generate vertives  / edges / faces with the add* methods.
   *
   * \author Tobi
   * \date 06.07.2012
   */
  virtual void createGeometry(){};
  void deleteGeometry();

  virtual bool initializeObject();
  virtual void cleanupObject();
private:
  bool correctEdge(HalfEdge * edge);

};
}