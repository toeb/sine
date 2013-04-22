#pragma once
#include <core.h>
#include <visualization/Renderer.h>
#include <simulation.kinematics/CoordinateSystem.h>
namespace nspace{
  class Viewport : virtual public NamedObject, public virtual PropertyChangingObject{
    reflect_type(Viewport);
  public:
    typedef Renderer * reflect_property(ViewportRenderer);
    typedef int reflect_property(Width);
    REFERENCE(public, int, Width);
    typedef int reflect_property(Height);    
    REFERENCE(public, int, Height);
    auto after_set(Height);
    auto after_set(Width);
  public:

    Real aspectRatio()const;

    Viewport();
    void resize(int width, int height);

    //renders the renderer into of viewport
    void render();

  protected:
    // is called first when entering the render method
    virtual void onBeforeRender(){}
    // is called after all renderers' onBeforeRender Method was called
    virtual void onBeginRender(){}
    // is called after all renderers were renderered
    virtual void onAfterRender(){}
    virtual void onResize(int newWidth, int newHeight){}
  private:
    void doResize(int width,int height);
  };
}