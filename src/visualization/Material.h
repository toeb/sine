#include <math/core.h>
#pragma once


namespace nspace{
  class VisualMaterial{
  private:
    Vector3D ambient;
    Vector3D diffuse;
    Vector3D specular;
    Real shininess;
    Real alpha;
  public:
    VisualMaterial(){};
    VisualMaterial(
      Real r,
      Real g,
      Real b, 
      Real ambient,
      Real diffuse, 
      Real specular, 
      Real alpha, 
      Real shininess)
      : shininess(shininess), alpha(alpha){
        this->ambient.x()=r*alpha;
        this->ambient.y()=g*alpha;
        this->ambient.z()=b*alpha; 

        this->diffuse.x()=r*alpha;
        this->diffuse.y()=g*alpha;
        this->diffuse.z()=b*alpha; 

        this->specular.x()=r*alpha;
        this->specular.y()=g*alpha;
        this->specular.z()=b*alpha; 
    };
    VisualMaterial(
      Real Ra,
      Real Ga,
      Real Ba,
      Real Rd,
      Real Gd,
      Real Bd,
      Real Rs,
      Real Gs,
      Real Bs,
      Real alpha,
      Real shininess
      ){
        ambient.x()=Ra;
        ambient.y()=Ga;
        ambient.z()=Ba; 

        diffuse.x()=Rd;
        diffuse.y()=Gd;
        diffuse.z()=Bd; 

        specular.x()=Rs;
        specular.y()=Gs;
        specular.z()=Bs; 
        this->alpha = alpha;
        this->shininess = shininess;
    };
    
  };
}