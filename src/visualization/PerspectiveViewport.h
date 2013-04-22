#pragma once

#include <visualization/Viewport.h>

namespace nspace{
  class PerspectiveViewport : public virtual Viewport{
    reflect_type(PerspectiveViewport);
    reflect_superclasses(Viewport);
  private:
    typedef CoordinateSystem reflect_property(Coordinates);
  public: property_reference(Coordinates);

    typedef Real reflect_property(FieldOfViewAngle);
  public:property_reference(FieldOfViewAngle);

    typedef Real reflect_property(NearCutOffPlane);
  public:property_reference(NearCutOffPlane);

    typedef Real reflect_property(FarCutOffPlane);
  public:property_reference(FarCutOffPlane);

    typedef Real reflect_property(ZoomFactor);
  public:property_reference(ZoomFactor);

  public:
    PerspectiveViewport();

    void onBeginRender(){viewportTransform();}

  protected:
    virtual void viewportTransform()=0;
  };
}