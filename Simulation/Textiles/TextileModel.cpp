#include "TextileModel.h"
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
using namespace IBDS;

void forallSprings(vector<DampedSpring*> & v, function<void(DampedSpring*)> f){
  for_each(v.begin(),v.end(), f);
}

TextileModel * TextileModel::createTextileModel(int gridrows, int gridcolumns, const Vector3D & topleft, const Vector3D & bottomright, const Vector3D & normal){
  Real spacing=0.5;
  Real particleMass=1;
  
  TextileModel & model = *(new TextileModel());
  model.rows = gridrows;
  model.columns = gridcolumns;
  
  
  for(int i=0; i < gridrows; i++){
    for(int j = 0; j < gridcolumns;j++){
      auto node = model.getNode(i,j);
      node.particle = new Particle();
      node.particle->setMass(particleMass);
      node.particle->setPosition(Vector3D());
    }
  }

  return &model;
}

TextileNode& TextileModel::getNode(int i, int j){
  int index = i*columns+j;
  //if(index >= rows*columns)return 0;
  //return  (_nodes.at(index));
  return *(new TextileNode());
}

void TextileModel::normalize(){

}



void TextileModel::setElongationSpringConstant(Real k_s){
  _k_s_elongation = k_s;
  forallSprings(_elongationSprings,[&k_s](DampedSpring* spring){
    spring->setStiffnessConstant(k_s);
  });
}
void TextileModel::setShearSpringConstant(Real k_s){
  _k_s_shear = k_s;
  forallSprings(_shearSprings,[&k_s](DampedSpring* spring){
    spring->setStiffnessConstant(k_s);
  });
}
void TextileModel::setFlexionSpringConstant(Real k_s){
  _k_s_flexion = k_s;
  forallSprings(_flexionSprings,[&k_s](DampedSpring* spring){
    spring->setStiffnessConstant(k_s);
  });
}
void TextileModel::setElongationDampeningConstant(Real k_d){
  _k_d_elongation = k_d;
   forallSprings(_elongationSprings,[&k_d](DampedSpring* spring){
    spring->setDampeningConstant(k_d);
  });
}
void TextileModel::setShearDampeningConstant(Real k_d){
  _k_d_shear = k_d;
    forallSprings(_shearSprings,[&k_d](DampedSpring* spring){
    spring->setDampeningConstant(k_d);
  });
}
void TextileModel::setFlexionDampeningConstant(Real k_d){
  _k_d_flexion = k_d;
    forallSprings(_flexionSprings,[&k_d](DampedSpring* spring){
    spring->setDampeningConstant(k_d);
  });
}
       
Real TextileModel::getElongationSpringConstant(Real k_d_e)const{
  return _k_s_elongation;
}
Real TextileModel::getShearSpringConstant(Real k_d_s)const{
  return _k_s_shear;
}
Real TextileModel::getFlexionSpringConstant(Real k_d_f)const{
  return _k_s_flexion;
}
Real TextileModel::getElongationDampeningConstant(Real k_d_e)const{
  return _k_d_elongation;
}
Real TextileModel::getShearDampeningConstant(Real k_d_s)const{
  return _k_d_shear;
}
Real TextileModel::getFlexionDampeningConstant(Real k_d_f)const{
  return _k_d_flexion;
}