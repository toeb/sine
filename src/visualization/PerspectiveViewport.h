#pragma once

#include <visualization/Viewport.h>

namespace nspace{
  class PerspectiveViewport : public virtual Viewport{
    REFLECTABLE_OBJECT(PerspectiveViewport);
  private:

    PROPERTY(CoordinateSystem,Coordinates){}
    REFERENCE(public,CoordinateSystem, Coordinates);
    PROPERTY(Real, FieldOfViewAngle){}
    REFERENCE(public,Real, FieldOfViewAngle);
    PROPERTY(Real, NearCutOffPlane){}
    REFERENCE(public,Real, NearCutOffPlane);
    PROPERTY(Real, FarCutOffPlane){}
    REFERENCE(public,Real, FarCutOffPlane);
    PROPERTY(Real, ZoomFactor){}
    REFERENCE(public,Real, ZoomFactor);

  public:
    PerspectiveViewport();

    void onBeginRender(){viewportTransform();}

  protected:
    virtual void viewportTransform()=0;
  };
}