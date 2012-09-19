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
 * \file src/vis/opengl/GeneralRenderers/CompositeRenderer.h
 */
#pragma once
#include <visualization/IRenderer.h>
#include <vector>
namespace nspace{

/**
 * \brief Composite renderer. Groups together multiple children
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class CompositeRenderer : public IRenderer{
public:

  /**
   * \brief Adds a renderer to this composite
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void addRenderer(IRenderer & renderer);

  /**
   * \brief Removes the renderer described by renderer from this composite.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param [in,out] renderer If non-null, the renderer.
   */
  void removeRenderer(IRenderer & renderer);

  void onBeforeRendering();
  virtual void render();
  void sceneResized(int newWidth, int newHeight);

protected:
  void cleanupObject();
  bool initializeObject();
private:  
  ///< The child renderers
  std::vector<IRenderer*> renderers;
};//class  CompositeRenderer
}//namespace mbslib
