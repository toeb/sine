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
#pragma once
#include <visualization.opengl/GlViewport.h>
#include <simulation.interaction/IInputListener.h>
#include <simulation.kinematics/KinematicCoordinates.h>
#include <simulation.time/PeriodicTask.h>
#include <simulation.integration/implementations/ExplicitEuler.h>
#include <core.hub/CompositeHubObject.h>
/**
 * \file src/vis/opengl/FpsCamera.h
 */
#include <simulation/SimulationTask.h>
#include <visualization/ViewportController.h>
namespace nspace{
  class FpsCamera :
    public virtual ViewportController,
    public virtual CompositeHubObject, 
    public virtual PeriodicTask
  {
    TYPED_OBJECT(FpsCamera);
	public:
    virtual void toString(std::ostream & out)const{CompositeHubObject::toString(out);}
    FpsCamera();
		void setInputHandler(InputHandler * handler){
			_handler = handler;
		}
		void onMouseMove(int x , int y, int dx, int dy);
    void timeout(Time timePassed,Time time);
    KinematicBody & kinematicBody(){return body;}
  protected:
    void onViewportAdded(Viewport * viewport);
    void onViewportRemoved(Viewport * viewport);
	private:
		InputHandler * _handler;
    Real roll,pitch,yaw;
    KinematicBody body;
    ExplicitEuler eulerIntegrator;
	};
}