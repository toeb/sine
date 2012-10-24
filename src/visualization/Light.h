#pragma once
#include <visualization/Color.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <core/Reflection.h>
#include <core/PropertyChangingObject.h>
#include <simulation.logging/Log.h>
#include <core/NamedObject.h>
#define PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME) REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)

namespace nspace{
  class Light : public virtual NamedObject, public virtual PropertyChangingObject,public virtual Log{
   TYPED_OBJECT(Light);
   REFLECTABLE(Light);
   // properties of 
   PROP(Color, AmbientColor){}
   PROP(Real, AmbientIntensity){
    if(newvalue>1){
      logWarning("clamping AmbientIntensity to 1");
      newvalue=1;
    }
    if(newvalue<0){
      logWarning("clamping AmbientIntensity to 0");
      newvalue=0;
    }   
   }
   PROP(Color, DiffuseColor){}
   PROP(Real, DiffuseIntensity){
    if(newvalue>1){
      logWarning("clamping DiffuseIntensity to 1");
      newvalue=1;
    }
    if(newvalue<0){
      logWarning("clamping DiffuseIntensity to 0");
      newvalue=0;
    }  
   }
   PROP(Color, SpecularColor){}
   PROP(Real, SpecularIntensity){
    if(newvalue>1){
      logWarning("clamping SpecularIntensity to 1");
      newvalue=1;
    }
    if(newvalue<0){
      logWarning("clamping SpecularIntensity to 0");
      newvalue=0;
    }   
   }
   PROP(CoordinateSystem, Coordinates){}
  public:
   Light();

 };
}