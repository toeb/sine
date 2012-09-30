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
#include "OffsetRenderer.h"
#include <visualization.opengl/MiniGL.h>
#include <simulation/Simulation.h>
using namespace nspace;
OffsetRenderer::OffsetRenderer(IRenderer & renderer):_renderer(renderer){}
void OffsetRenderer::render(Viewport & viewport){
  MiniGL::pushMatrix();
  MiniGL::translate(position());
  MiniGL::multQuaternion(orientation());
  _renderer.render(viewport);
  MiniGL::popMatrix();
}

bool OffsetRenderer::initializeObject(){
  //add original renderer to simulation
  *simulation() << _renderer;
  // set original renderer to ignore.  causing the rendermodule not to run the render method
  _renderer.setIgnore(true);
  return true;
}