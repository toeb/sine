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

#include <math/core.h>

#include <visualization.opengl/opengl.h>
#include <visualization.opengl/Utility.h>

#include "GlViewport.h"

using namespace nspace;
Color & GlViewport::clearColor(){
  return _clearColor;
}
const Color & GlViewport::clearColor()const{
  return _clearColor;
}
void GlViewport::viewportTransform(){		
  initialize();
	glViewport (0, 0, width(), height());

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective (fieldOfViewAngle()/M_PI*180, aspectRatio(), nearCutOffPlane(), farCutOffPlane()); 

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
  glScale(zoomFactor());
  glTransformation(coordinates()); 

  glClearColor(_clearColor.r(),_clearColor.g(),_clearColor.b(),_clearColor.a());
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}

bool GlViewport::initializeObject(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

GlViewport::GlViewport(){
  _clearColor.setTo("LightGrey");
}