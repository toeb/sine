#include "Light.h"

using namespace nspace;



Light::Light():
  _Coordinates(CoordinateSystem::identity()),
  _AmbientIntensity(0.2),_DiffuseIntensity(0.9),_SpecularIntensity(1)
,_AmbientColor(1,1,1,1)
,_SpecularColor(1,1,1,1)
,_DiffuseColor(1,0,0,1)
{
  setName("Light");
  Coordinates().position()=Vector3D(-10,10,10);
}
