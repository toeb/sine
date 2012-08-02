


#pragma once
#include <visualization/core/IRenderer.h>
#include <simulation/kinematics/CoordinateSystem.h>
#include <math/definitions.h>

namespace nspace{

class Transformation : CoordinateSystem{
public:
  ValueHolder<Vector3D> scale;
  ValueHolder<Vector3D> skew;
  
  void getTransformationMatrix(Matrix4x4 & T);
  Matrix4x4 getTransformationMatrix();
};
/**
 * \brief
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class OffsetRenderer :public IRenderer, public CoordinateSystem{
private:
  IRenderer & _renderer;
 
public:

  /**
   * \brief Default constructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  OffsetRenderer(IRenderer & renderer);
  /**
   * \brief Renders this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void render();
protected:
  bool initializeObject();
};//class OffsetRenderer
}
