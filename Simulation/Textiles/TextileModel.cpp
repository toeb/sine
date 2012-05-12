#include "TextileModel.h"

using namespace IBDS;

TextileModel * TextileModel::createTextileModel(int gridwidth, int gridheight){
  return 0;
}

void TextileModel::normalize(){

}

void TextileModel::setElongationSpringConstant(Real k_s){
  _k_s_elongation = k_s;
}
void TextileModel::setShearSpringConstant(Real k_s){
  _k_s_shear = k_s;
}
void TextileModel::setFlexionSpringConstant(Real k_s){
  _k_s_flexion = k_s;
}
void TextileModel::setElongationDampeningConstant(Real k_d){
  _k_d_elongation = k_d;
}
void TextileModel::setShearDampeningConstant(Real k_d){
  _k_d_shear = k_d;
}
void TextileModel::setFlexionDampeningConstant(Real k_d){
  _k_d_flexion = k_d;
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