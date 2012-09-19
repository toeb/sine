

/**
 * \file src/vis/opengl/GeneralRenderers/VectorRenderer.h
 */
#pragma once
#include <visualization/IRenderer.h>
#include <math/definitions.h>
namespace nspace{

/**
 * \brief Vector renderer. draws an vector to the scene NOTIMPLEMENTED!
 *
 * 
 */
class VectorRenderer : public IRenderer{
public:

  /**
   * \brief Constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param [in,out] position The position.
   * \param [in,out] vector   The vector.
   * \param color             (optional) [in,out] The color.
   */
  VectorRenderer(Vector3D & position, Vector3D & vector, Vector3D & color =  *(new Vector3D(1,1,1)));

  /**
   * \brief Renders this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void render();
private :
  ///< The position
  Vector3D & _position;
  ///< The vector
  Vector3D & _vector;
  ///< The color
  Vector3D & _color;
};


}

