#pragma once
#include <config.h>
#include <visualization/Color.h>
#include <core/Reflection.h>
#include <core/PropertyChangingObject.h>
#define PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME); REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)
namespace nspace{
class Material : public virtual PropertyChangingObject{
  TYPED_OBJECT(Material);
  REFLECTABLE(Material);
private:
  PROP(Color,Ambient){}
  PROP(Color,Diffuse){}
  PROP(Color,Specular){}
  PROP(Color,Emission){}
  PROP(Real,Shininess){}
  PROP(std::string, MaterialName){}
     
  
  static std::map<std::string, Material*> & _palette;
   
public: 
  void setTo(const std::string & name);
    static const  Material& unknown; 
    static int loadMaterials(const std::string & filename);
    static const Material & getMaterialByName(const std::string & name);
    Material();
 Material(const Color & color);

 Material(const std::string &name, const Color & ambient, const Color & diffuse, const Color & specular, const Color & emission, Real shininess);
 Material(const std::string & name);

 Material(const Material & material);
 Material & operator =(const Material& material);


};
}
