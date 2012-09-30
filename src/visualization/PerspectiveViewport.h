#pragma once

#include <visualization/Viewport.h>
namespace nspace{
  class PerspectiveViewport : public virtual Viewport{
  private:
    CoordinateSystem _coordinates;
    Real _fieldOfViewAngle;
    Real _nearCutOffPlane;
    Real _farCutOffPlane;
    Real _zoomFactor;
  public:
    PerspectiveViewport():_fieldOfViewAngle(M_PI/ 4), _nearCutOffPlane(0.1),_farCutOffPlane(100.0), _zoomFactor(1.0){}
    inline CoordinateSystem & coordinates(){return _coordinates;}
    inline Real & fieldOfViewAngle(){return _fieldOfViewAngle;}
    inline Real & nearCutOffPlane(){return _nearCutOffPlane;}
    inline Real & farCutOffPlane(){return _farCutOffPlane;}
    inline Real & zoomFactor(){return _zoomFactor;}
    void onBeforeRender(){}

  protected:
    virtual void viewportTransform()=0;
  };
  }