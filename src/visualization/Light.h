#pragma once
#include <visualization/Color.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <core.h>
#include <core.logging.h>
#include <core.property.h>
namespace nspace{
  class Light : public virtual NamedObject, public virtual PropertyChangingObject,public virtual Log{
    reflect_type(Light)
      // properties of
      typedef Color reflect_property(AmbientColor);
    typedef Real reflect_property(AmbientIntensity);
    auto before_set(AmbientIntensity){       
      if(*newvalue >1){
        logWarning("clamping AmbientIntensity to 1");
        setAmbientIntensity(1);
        return Cancel;
      }
      if(*newvalue <0){
        logWarning("clamping AmbientIntensity to 0");
        setAmbientIntensity(0);
        return Cancel;
      }
      return Accept;
    }
    typedef Color reflect_property(DiffuseColor);
    typedef Real reflect_property(DiffuseIntensity);
    auto before_set(DiffuseIntensity){       
      if(*newvalue >1){
        logWarning("clamping DiffuseIntensity to 1");
        setDiffuseIntensity(1);
        return Cancel;
      }
      if(*newvalue <0){
        logWarning("clamping DiffuseIntensity to 0");
        setDiffuseIntensity(0);
        return Cancel;
      }
      return Accept;
    }
    typedef Color reflect_property(SpecularColor);
    typedef Real reflect_property(SpecularIntensity);
    auto before_set(SpecularIntensity){       
      if(*newvalue >1){
        logWarning("clamping SpecularIntensity to 1");
        setSpecularIntensity(1);
        return Cancel;
      }
      if(*newvalue <0){
        logWarning("clamping SpecularIntensity to 0");
        setSpecularIntensity(0);
        return Cancel;
      }
      return Accept;
    }

    typedef CoordinateSystem reflect_property(Coordinates);
  public:property_reference(Coordinates);
  public:
    Light();
  };
}
