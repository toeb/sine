#pragma once
#include <Simulation/Geometry/Polygon/Polygon.h>
#include <Math/Vector2D.h>
namespace IBDS{

/**
* \brief Ply mesh. Represents a Mesh loaded from a ply file.
* 				
*/
struct PlyVertex : public Vertex{
  Vector3D normal;
  Vector2D textureCoordinates;
  float color[4];
};

class PlyMesh : public Polygon {  
 public:

  /**
   * \brief Constructor.
   * 				
   * \param _filename Filename of the .ply file.
   */
  PlyMesh(const std::string & _filename):
       filename(_filename){};

  /**
   * \brief Constructor.
   *
   * 
   * \param _filename Filename of the file.
   */
  PlyMesh(const char * _filename):filename(*(new std::string(_filename))){}

  PlyVertex * addPlyVertex();
  void createFace(Index a,Index b,Index c);
protected:
  Vertex * createVertex();

  void createGeometry();

  ///< Filename of the file
  const std::string & filename;
};//class PlyMesh
}
