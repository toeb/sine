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
* \file src/vis/opengl/GlViewport.h
*/
#pragma once
#include <simulation.logging/LoggingObject.h>
#include <visualization/PerspectiveViewport.h>
#include <core.initialization/Initializable.h>
#include <visualization/Color.h>
namespace nspace{
  class GlViewport:public virtual PerspectiveViewport, public virtual Initializable{
    TYPED_OBJECT(GlViewport);
    Color _clearColor;

  public:
    GlViewport();
    Color& clearColor();
    const Color& clearColor()const;


    void viewportTransform();
  protected:
    void onBeforeRender();
    bool initializeObject();
  };//class GlViewport

}//namespace mbslib
