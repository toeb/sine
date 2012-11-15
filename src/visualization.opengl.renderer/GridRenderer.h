
#pragma once

/**
 * \file src/vis/opengl/GeneralRenderers/GridRenderer.h
 */
#include <visualization/Renderer.h>
#include <core.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <visualization/Material.h>


#define PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME); REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)
namespace nspace{



/**
 * \brief Grid renderer. Renders a xz-plane as a Grid at a given y position
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class GridRenderer : public virtual Renderer, public virtual PropertyChangingObject,public virtual NamedObject{
  TYPED_OBJECT(GridRenderer);
  REFLECTABLE(GridRenderer);
public:
  PROP(CoordinateSystem,Coordinates){}
  PROP(int, Sections){}
  PROP(Real, Width){}
  PROP(Real, Height){}
  PROP(Material, GridMaterial){}

public:

  /**
   * \brief Constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param y_where   The y coordinate where to render the grid.
   * \param _width    (optional) the width of the grid.
   * \param _height   (optional) the breadth of the grid.
   * \param _sections (optional) the number of sections in one direction.
   */
  GridRenderer();

  /**
   * \brief Renders this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void render();
};//class GridRenderer
}