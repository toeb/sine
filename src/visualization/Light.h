#pragma once
#include <visualization/Color.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <core.h>
#include <core.logging.h>

namespace nspace{
  class Light : public virtual NamedObject, public virtual PropertyChangingObject,public virtual Log{
    REFLECTABLE_OBJECT(Light)
      // properties of
      REF_PROP(Color, AmbientColor){}
    REF_PROP(Real, AmbientIntensity){
      if(newvalue>1){
        logWarning("clamping AmbientIntensity to 1");
        newvalue=1;
      }
      if(newvalue<0){
        logWarning("clamping AmbientIntensity to 0");
        newvalue=0;
      }
    }
    REF_PROP(Color, DiffuseColor){}
    REF_PROP(Real, DiffuseIntensity){
      if(newvalue>1){
        logWarning("clamping DiffuseIntensity to 1");
        newvalue=1;
      }
      if(newvalue<0){
        logWarning("clamping DiffuseIntensity to 0");
        newvalue=0;
      }
    }
    REF_PROP(Color, SpecularColor){}
    REF_PROP(Real, SpecularIntensity){
      if(newvalue>1){
        logWarning("clamping SpecularIntensity to 1");
        newvalue=1;
      }
      if(newvalue<0){
        logWarning("clamping SpecularIntensity to 0");
        newvalue=0;
      }
    }
    REF_PROP(CoordinateSystem, Coordinates){}
  public:
    Light();
  };
}
