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

#ifndef __mbslib_OffsetRenderer_h__
#define __mbslib_OffsetRenderer_h__
#include <vis/IRenderer.h>
#include <simulation/kinematics/CoordinateSystem.h>
#include <simulation/math/Matrix4x4.h>
namespace mbslib{

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
}//namespace mbslib
#endif
