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
 * \file src/vis/opengl/OpenGlRenderer.h
 */
#pragma once
#include <visualization/core/RenderModule.h>
#include <visualization/core/IRenderer.h>
#include <visualization/core/composite/CompositeRenderer.h>
#include <visualization/core/Color.h>
namespace nspace{
/**
 * \brief Open gl renderer.
 */
class OpenGLRenderModule : public RenderModule {
private:
	Color _clearColor;
public:
  Color & clearColor(){
    return _clearColor;
  }
  const Color & clearColor()const{
    return _clearColor;
  }

  /**
   * \brief Default constructor.
   */
  OpenGLRenderModule(){
		setName("OpenGL RenderEngine");
		clearColor().setTo("LightGreen");
	};

  /**
   * \brief Destructor.
   */
  ~OpenGLRenderModule(){};
  

	

protected:
	bool initializeRenderEngine();
	void cleanupRenderEngine();
	virtual bool initializeGlRenderEngine(){return true;}
	virtual void cleanupGlRenderEngine(){}
	void onBeforeRender();
private:
  void clear();
};//class OpenGLRenderer

};//namespace mbslib
