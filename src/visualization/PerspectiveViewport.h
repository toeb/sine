#pragma once

#include <visualization/Viewport.h>



namespace nspace{
  class PerspectiveViewport : public virtual Viewport{
    REFLECTABLE_OBJECT(PerspectiveViewport);
  private:

    PROPERTY(CoordinateSystem,Coordinates){}
    PROPERTY(Real, FieldOfViewAngle){}
    PROPERTY(Real, NearCutOffPlane){}
    PROPERTY(Real, FarCutOffPlane){}
    PROPERTY(Real, ZoomFactor){}

  public:
    PerspectiveViewport();


    void onBeginRender(){viewportTransform();}

  protected:
    virtual void viewportTransform()=0;
  };
  }