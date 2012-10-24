#pragma once
#include <config.h>
#include <visualization/Color.h>
#include <core/Reflection.h>
#include <core/PropertyChangingObject.h>


namespace nspace{
class Material : public virtual PropertyChangingObject{
  REFLECTABLE_OBJECT(Material);
private:
  REF_PROP(Color,Ambient){}
  REF_PROP(Color,Diffuse){}
  REF_PROP(Color,Specular){}
  REF_PROP(Color,Emission){}
  REF_PROP(Real,Shininess){}
  REF_PROP(std::string, MaterialName){}
     
  
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
