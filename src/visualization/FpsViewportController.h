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
#include <core.hub/CompositeHubObject.h>
#include <core.task/ScheduledTask.h>

#include <visualization.opengl/GlViewport.h>
#include <simulation.interaction/IInputListener.h>
#include <simulation.kinematics/KinematicCoordinates.h>
#include <simulation.integration/implementations/ExplicitEuler.h>
#include <simulation/SimulationTask.h>

#include <core.logging.h>

#include <visualization/ViewportController.h>

namespace nspace{
  class FpsViewportController:
    public virtual ViewportController,
    public virtual CompositeHubObject,
    public virtual ScheduledTask,
    public virtual IInputListener,
    public virtual Log
  {
    REFLECTABLE_OBJECT(FpsViewportController);
    SUBCLASSOF(Log);
    SUBCLASSOF(ScheduledTask);
    SUBCLASSOF(ViewportController);

    PROPERTY(Real, Roll){}
    CUSTOMSERIALIZER(Real,Roll,);
    CUSTOMDESERIALIZER(Real,Roll,);

    PROPERTY(Real, Pitch){}
    CUSTOMSERIALIZER(Real,Pitch,);
    CUSTOMDESERIALIZER(Real,Pitch,);

    PROPERTY(Real, Yaw){}
    CUSTOMSERIALIZER(Real,Yaw,);
    CUSTOMDESERIALIZER(Real,Yaw,);

    DESCRIPTION(MovementSpeed,"The speed at which to translate when pressing keys");
    PROPERTY(Real,MovementSpeed){}

    DESCRIPTION(RotationSpeed,"The speed at which to rotate");
    PROPERTY(Real,RotationSpeed){}

  public:
    FpsViewportController();
    void onMouseMove(InputHandler * sender, int x , int y, int dx, int dy);
    void calculateRotation();
    void timeout(Time timePassed,Time time);
    KinematicBody & kinematicBody(){return body;}
    virtual void toString(std::ostream & out)const{CompositeHubObject::toString(out);}
  protected:
    void onViewportAdded(Viewport * viewport);
    void onViewportRemoved(Viewport * viewport);
  private:
    KinematicBody body;
    ExplicitEuler eulerIntegrator;
  };
}
