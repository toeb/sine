

/**
 * \file src/vis/opengl/GeneralRenderers/CoordinateSystemRenderer.h
 */
#pragma once
#include <visualization/IRenderer.h>
#include <simulation.kinematics/CoordinateSystem.h>

namespace nspace{

/**
 * \brief Class renders a coordinate system
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class CoordinateSystemRenderer : public IRenderer
{
private:
  CoordinateSystem & _coordinateSystem;
public:

  CoordinateSystemRenderer(CoordinateSystem  & coordinateSystem):_coordinateSystem(coordinateSystem){

  }

  /**
    * \brief Renders this object.
    *
    */
  void render();
};

}