#include "Material.h"
#include <fstream>
using namespace nspace;
using namespace std;


  const  Material& Material::unknown = *new Material;   
  std::map<std::string, Material*> & Material::_palette = *new std::map<std::string, Material*>();

  int Material::loadMaterials(const std::string & filename){
    ifstream file(filename,ifstream::in);
    if(!file.good())return 0;
    int materialsLoaded = 0;
    while(file.good()){
      std::string name;
      Material * m = new Material;
      
      file >> m->Ambient().r();
      file >> m->Ambient().g();
      file >> m->Ambient().b();
      file >> m->Ambient().a();

      file >> m->Diffuse().r();
      file >> m->Diffuse().g();
      file >> m->Diffuse().b();
      file >> m->Diffuse().a();

      file >> m->Specular().r();
      file >> m->Specular().g();
      file >> m->Specular().b();
      file >> m->Specular().a();
      
      file >> m->Emission().r();
      file >> m->Emission().g();
      file >> m->Emission().b();
      file >> m->Emission().a();
      
      file>> m->Shininess();
      
      getline(file,name);

      name = name.substr(1);
      m->MaterialName() = name;
      _palette[name]= m;
      materialsLoaded++;
  }  
  return materialsLoaded;
      
  }
  const Material & Material::getMaterialByName(const std::string & name){
      auto material = _palette[name];
      if(material)return *material;
      return unknown;
  }
  void Material::setTo(const std::string & name){
    auto mat = getMaterialByName(name);
    *this = mat;
  }

  Material::Material(){}
  Material::Material(const Color & color){
    _Ambient = color;
_Diffuse = color;
_Specular = color;
_Emission = Color(0,0,0,0);
_Shininess = 10;

  }
  Material::Material(const std::string & name){
    setTo(name);
  
  }

  
 Material::Material(const Material & material){
   *this = material;
 }
 Material & Material::operator =(const Material& material){
      _Ambient=material.Ambient();
   _Diffuse=material.Diffuse();
   _Specular=material.Specular();
   _Emission=material.Emission();
   _Shininess=material.Shininess();
   _MaterialName=material.MaterialName();
   return *this;
 }

