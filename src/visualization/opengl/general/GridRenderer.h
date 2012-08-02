/*
 * Copyright (C) 2011
 * Simulation, Systems Optimization and Robotics Group (SIM)
 * Technische Universitaet Darmstadt
 * Hochschulstr. 10
 * 64289 Darmstadt, Germany
 * www.sim.tu-darmstadt.de
 *
 * This file is part of the mbslib.
 * All rights are reserved by the copyright holder.
 *
 * The mbslib is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You may use the mbslib or parts of it only with the written permission of the copyright holder.
 * You may NOT modify or redistribute any part of the mbslib without the prior written
 * permission by the copyright holder.
 *
 * Any violation of the rights and restrictions mentioned above will be prosecuted by civil and penal law.
 * Any expenses associated with the prosecution will be charged against the violator.
 */

/**
 * \file src/vis/opengl/GeneralRenderers/GridRenderer.h
 */
#ifndef __mbslib_GridRenderer_h__
#define __mbslib_GridRenderer_h__
#include <vis/IRenderer.h>
namespace mbslib{
	
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
}//namespace mbslib
#endif