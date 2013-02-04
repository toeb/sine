

/**
 * \file src/vis/opengl/GeneralRenderers/CoordinateSystemRenderer.h
 */
#pragma once
#include <visualization/Renderer.h>
#include <simulation.kinematics/CoordinateSystem.h>

namespace nspace{

/**
 * \brief Class renders a coordinate system
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class CoordinateSystemRenderer : public Renderer
{
private:
  const CoordinateSystem & _coordinateSystem;
public:

  CoordinateSystemRenderer(const CoordinateSystem  & coordinateSystem);

  /**
    * \brief Renders this object.
    *
    */
  void render();
};

}