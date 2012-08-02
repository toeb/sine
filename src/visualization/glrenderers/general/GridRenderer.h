

/**
 * \file src/vis/opengl/GeneralRenderers/GridRenderer.h
 */
#pragma once
#include <visualization/core/IRenderer.h>
namespace nspace{
	
class MeshGridRenderer : public IRenderer{
public:
	void render();
};

/**
 * \brief Grid renderer. Renders a xz-plane as a Grid at a given y position
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class GridRenderer : public IRenderer{
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
  GridRenderer(
    double y_where, 
    double _width=20, 
    double _height=20,
    int _sections = 20)
    :width(_width)
    ,height(_height)
    ,sections(_sections)
    ,y(y_where){}

  /**
   * \brief Renders this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void render();
private:
  ///< The width
  double width;
  ///< The height
  double height;
  ///< The y coordinate
  double y;
  ///< The sections
  int sections; 
};//class GridRenderer
}