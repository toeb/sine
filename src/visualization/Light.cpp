#include "Light.h"

using namespace nspace;

Light::Light():
  _AmbientColor(1,1,1,1)
  ,_AmbientIntensity(0.2)
  ,_DiffuseColor(1,0,0,1)
  ,_DiffuseIntensity(0.9)
  ,_SpecularColor(1,1,1,1)
  ,_SpecularIntensity(1)
  ,_Coordinates(CoordinateSystem::identity())
{
  setName("Light");
  Coordinates().position()=Vector3D(-10,10,10);
}