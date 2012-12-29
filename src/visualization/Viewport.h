#pragma once
#include <core.h>
#include <visualization/Renderer.h>
#include <simulation.kinematics/CoordinateSystem.h>
namespace nspace{
  class Viewport : virtual public NamedObject, public virtual PropertyChangingObject{
    REFLECTABLE_OBJECT(Viewport);
  public:
    PROPERTY(Renderer *, ViewportRenderer){}
    PROPERTY(int,Width);
    REFERENCE(public, int, Width);
    PROPERTY(int, Height);
    REFERENCE(public, int, Height);
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