#ifndef __mbslib_Mesh_h__
#define __mbslib_Mesh_h__
#include <vis/IRenderer.h>
#include <simulation/math/types.h>
#include <functional>

namespace mbslib{
typedef unsigned int Index;
struct MeshElement{
  Index id;
};
struct Vertex:public MeshElement{
  Vector3D position;
  Vector3D normal;
};
struct Face:public MeshElement{
  std::vector<Vertex*> vertices; 
};


/**
 * \brief Generic  Mesh. 
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class Mesh : public ISimulationObject{
private:
  std::vector<Vertex * > _vertices;
  std::vector<Face * > _faces;
public:

  /**
   * \brief Default constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  Mesh(){};


  void normalize();
  void foreachVertex(std::function<void (Vertex *)> f);
  void foreachFace(std::function<void (Face*)> f);

  Vertex* addVertex(Vertex * vertex);
  Vertex* addVertex(const Vector3D & position, const Vector3D & normal);  
  Face* addFace(Index a, Index b, Index c);
  Face* addFace(Vertex *a, Vertex *b, Vertex *c);
  Face* addFace(Face * face);
  Face * face(Index i);
  Vertex * vertex(Index i);
protected:
  
  virtual void load()=0;
    /**
   * \brief Initializes this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  bool initializeObject();

  /**
   * \brief Destroys this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void cleanupObject();



};//class Mesh


}//namespace mbslib
#endif