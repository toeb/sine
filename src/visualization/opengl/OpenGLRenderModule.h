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

namespace nspace{
/**
 * \brief Open gl renderer.
 */
class OpenGLRenderModule : public RenderModule {
private:
	double _clearColor[4];
public:

	void setClearColor(double r, double g, double b, double a){_clearColor[0] = r;_clearColor[1] = g;_clearColor[2] = b;_clearColor[3] = a;};
	const double * getClearColor()const{return _clearColor;}

  /**
   * \brief Default constructor.
   */
  OpenGLRenderModule(){
		setName("OpenGL RenderEngine");
		setClearColor(0.95f, 0.95f, 1.0f, 1.0f);
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
