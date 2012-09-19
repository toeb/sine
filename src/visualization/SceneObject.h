#pragma once

#include <visualization/core/IRenderer.h>
#include <visualization/core/Color.h>
#include <visualization/core/Texture.h>

namespace nspace{
  class SceneObject : public virtual IRenderer{
    TYPED_OBJECT;
  private:
    Color _color;
    Texture  _texture;
    CoordinateSpace _coordinates;
  public:
    Color& color(){return _color;}
    Texture & texture(){return _texture;}
    CoordinateSpace & coordinates(){return _coordinates;}

    const Color& color()const{return _color;}
    const Texture & texture()const{return _texture;}
    const CoordinateSpace & coordinates()const{return _coordinates;}
    
    void render();

  };

}