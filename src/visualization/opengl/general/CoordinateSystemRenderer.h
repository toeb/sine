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
 * \file src/vis/opengl/GeneralRenderers/CoordinateSystemRenderer.h
 */
#pragma once
#include <vis/IRenderer.h>
#include <simulation/kinematics/CoordinateSystem.h>

namespace mbslib{

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