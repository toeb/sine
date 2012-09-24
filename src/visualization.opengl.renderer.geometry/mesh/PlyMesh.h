#pragma once

#include <visualization/IRenderer.h>
#include <string>
#include "Mesh.h"
namespace nspace{

/**
 * \brief Ply mesh. Represents a Mesh loaded from a ply file.
 * 				
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class PlyMesh : public Mesh{
private:
  Vertex * _currentVertex;
  Face * _currentFace;
public:
  void nextVertex();
  void nextFace();
  inline Vertex * currentVertex(){return _currentVertex;}
  inline Face * currentFace(){return _currentFace;}

  /**
   * \brief Constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param _filename Filename of the .ply file.
   */
  PlyMesh(const std::string & _filename):
       filename(_filename),_currentVertex(new Vertex()),_currentFace(new Face()){};

  /**
   * \brief Constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param _filename Filename of the file.
   */
  PlyMesh(const char * _filename):filename(*(new std::string(_filename))),_currentVertex(new Vertex()),_currentFace(new Face()){}

  
protected:

  /**
   * \brief Loads.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param [in,out] vertices    If non-null, the vertices.
   * \param [in,out] indices     If non-null, the indices.
   * \param [in,out] vertexCount If non-null, number of vertices.
   * \param [in,out] faceCount   If non-null, number of faces.
   * \param [in,out] indexCount  If non-null, number of indexes.
   */
  void load();
  ///< Filename of the file
  const std::string & filename;

};//class PlyMesh
}//namespace mbslib
