#pragma once

#include <core.hub/CompositeHubObject.h>
#include <visualization.opengl.renderer/LightRenderer.h>

namespace nspace{
  
  class DefaultLightSetup : public virtual CompositeHubObject{
    TYPED_OBJECT(DefaultLightSetup)
  private:
    LightRenderer _lightRenderer;
    Light _light1;
    Light _light2;
    Light _light3;
  public:
    Light & light1(){return _light1;};
    Light & light2(){return _light2;};
    Light & light3(){return _light3;};
    LightRenderer & lightRenderer(){return _lightRenderer;}
    DefaultLightSetup(){
      
      _light1.Coordinates().position() = Vector3D(-10,10,10);
      _light2.Coordinates().position() = Vector3D(-10,10,-10);
      _light2.Coordinates().position() = Vector3D(10,10,10);

      components()|=&_lightRenderer;
      components()|=&_light1;
      components()|=&_light2;
      components()|=&_light3;
      _lightRenderer |= &_light1;
      _lightRenderer |= &_light2;
      _lightRenderer |= &_light3;
    }
    


  };

}
