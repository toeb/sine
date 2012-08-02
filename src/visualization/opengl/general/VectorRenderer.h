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
 * \file src/vis/opengl/GeneralRenderers/VectorRenderer.h
 */
#ifndef __mbslib_VectorRenderer_h__
#define __mbslib_VectorRenderer_h__
#include <vis/IRenderer.h>
#include <mbs/types.h>
namespace mbslib{

/**
 * \brief Vector renderer. draws an vector to the scene NOTIMPLEMENTED!
 *
 * \author Tobias Becker
 * \date 05.04.2012
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
  VectorRenderer(TVector3 & position, TVector3 & vector, TVector3 & color =  *(new TVector3(1,1,1)));

  /**
   * \brief Renders this object.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void render();
private :
  ///< The position
  TVector3 & _position;
  ///< The vector
  TVector3 & _vector;
  ///< The color
  TVector3 & _color;
};


}

#endif