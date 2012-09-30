#pragma once
#include <core/NamedObject.h>
#include <visualization/Renderer.h>
#include <simulation.kinematics/CoordinateSystem.h>
namespace nspace{
  class Viewport : virtual public NamedObject{
  private:
    Renderer * _renderer;
    int _width;
    int _height;
  public:
    Real aspectRatio()const;
    Viewport();
    void resize(int width, int height);
    const int & width()const;
    const int & height()const;
    void render();

  protected:
    virtual void onBeforeRender(){}
    virtual void onAfterRender(){}
    virtual void onResize(int newWidth, int newHeight){}
  };


}