#pragma once

#include <config.h>

#include <visualization/Renderer.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <math/core.h>

namespace nspace{

/**
 * \brief
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class OffsetRenderer :public Renderer, public CoordinateSystem{
  TYPED_OBJECT(OffsetRenderer);
private:
  Renderer & _renderer;
 
public:

  /**
   * \brief Default constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  OffsetRenderer(Renderer & renderer);
  /**
   * \brief Renders this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void render(Viewport & viewport);
protected:
  bool initializeObject();
};//class OffsetRenderer

}
