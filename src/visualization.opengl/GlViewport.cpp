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

void GlViewport::onBeforeRender(){
  // ensure object is initialized
  initialize();
  // clear screen before renderering
  glClearColor(_ClearColor.r(),_ClearColor.g(),_ClearColor.b(),_ClearColor.a());
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}
void GlViewport::viewportTransform(){
  // set viewport
  glViewport (0, 0, Width(), Height());

  // set perspectvive
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (FieldOfViewAngle()/M_PI*180, aspectRatio(), NearCutOffPlane(), FarCutOffPlane());

  // move viewport to correct position/orientation
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  glScale(ZoomFactor());
  glTransformation(Coordinates());
}

bool GlViewport::initializeObject(){
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
  return true;
}

GlViewport::GlViewport(){
  setClearColor(Color("LightGrey"));
}