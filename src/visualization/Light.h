#pragma once
#include <visualization/Color.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <core/Reflection.h>
#include <core/PropertyChangingObject.h>

#define PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME) REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)

namespace nspace{
  class Light : public virtual PropertyChangingObject{
   TYPED_OBJECT(Light);
   REFLECTABLE(Light);
   // properties of 
   PROP(Color, AmbientColor){}
   PROP(Real, AmbientIntensity){}
   PROP(Color, DiffuseColor){}
   PROP(Real, DiffuseIntensity){}
   PROP(Color, SpecularColor){}
   PROP(Real, SpecularIntensity){}
   PROP(CoordinateSystem, Coordinates){}
  public:
    Light();

 };
}