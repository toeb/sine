#include "TextileModel.h"
#include <algorithm>
#include <vector>
#include <Simulation/Dynamics/ParticleConnector.h>
#include <functional>
using namespace std;
using namespace IBDS;


void TextileModel::forAllNodes(function<void(int, int, TextileNode *)> f){
  forAll([&f,this](int i, int j){f(i,j,getNode(i,j));});
}

void TextileModel::forAll(function<void(int, int)> f){
  for(int i=0; i < _rows; i++){
    for(int j=0; j < _columns; j++){
      f(i,j);
    }
  }
}
void TextileModel::addSimulationObject(ISimulationObject  * obj){
  _simulationObjects.push_back(obj);
}

Particle * TextileModel::createParticle(TextileNode * node, Real mass, const Vector3D & position){
  Particle *p = node->particle;
  if(!p) {
    p = new Particle();
    node->connector = new ParticleConnector(*p);
    addSimulationObject(node->connector);
    addSimulationObject(p);
    node->particle = p;
  }
  p->setPosition(position);
  p->setMass(mass);
  addSimulationObject(p);
  return p;
}



DampedSpring * TextileModel::createSpring(TextileNode * nodeA, TextileNode * nodeB, Real k_s, Real k_d){
  
  
  Connector * a = nodeA->connector;
  Connector * b = nodeB->connector;
  Real l_0 = (a->getWorldPosition()-b->getWorldPosition()).length();
  DampedSpring * spring = new DampedSpring(*a,*b,k_s,k_d,l_0);
  addSimulationObject(spring);
  return spring;


}
void TextileModel::buildModel(
  const Vector3D & p, 
    const Matrix3x3 & orientation,
    Real width, Real height,
    int rows, int cols){

    _k_d_elongation=1;
    _k_s_elongation=20;
    _k_d_flexion=1;
    _k_s_flexion=20;
    _k_d_shear=1;
    _k_s_shear=20;
    _mass = 400;
  Real particleMass=_mass/(rows*cols);
  
  
  if(rows < 0) rows = static_cast<int>(height);
  if(rows < 3)  rows = 3;
  if(cols < 0) cols = static_cast<int>(width);
  if(cols < 3) cols = 3;
  
  _rows = rows;
  _columns = cols;

  Real spacingWidth = width/cols;
  Real spacingHeight = height/rows;
  
  Vector3D x1(orientation(0,0),orientation(1,0), orientation(2,0));
  Vector3D x2(orientation(0,1),orientation(1,1), orientation(2,1));
  x1.normalize();
  x2.normalize();

  // create particles with correct mass and positions
  for(int i=0; i < rows; i++){
    for(int j = 0; j < cols;j++){
      Vector3D position = x1*spacingWidth*(i-rows/2.0) + x2 * spacingHeight*(j-cols/2.0) + p;
      TextileNode * node = new TextileNode();
      createParticle(node,particleMass,position);
      _nodes.push_back( node);
    }
  }
  // set structure pointers
   for(int i=0; i < rows; i++){
    for(int j = 0; j < cols;j++){
        TextileNode * node = getNode(i,j);
        node->north = getNode(i-1,j);
        node->south = getNode(i+1,j);
        node->west =  getNode(i,j-1);
        node->east =  getNode(i,j+1);
    }
  }
  // create springs
  for(int i= 0; i < rows; i++){
    for(int j=0; j < cols; j++){
      
      TextileNode * node = getNode(i,j);

      if(node->east){
        if(!node->eastElongator){
          DampedSpring * spring =createSpring(node,node->east,_k_s_elongation,_k_d_elongation);
          node->eastElongator = spring;
          node->east->westElongator= spring;
        }
        if(!node->eastFlexor){
          if(node->east->east){
            DampedSpring * spring= createSpring(node, node->east->east, _k_s_flexion,_k_d_flexion);
            node->eastFlexor = spring;
            node->east->east->westFlexor =spring;
          }
        }
        if(!node->northEastShearer){
          if(node->east->north){
            DampedSpring * spring =createSpring(node, node->east->north, _k_s_shear,_k_d_shear);
            node->northEastShearer = spring;
            node->east->north->southWestShearer = spring;
          }
        }
      }
    }

}
}

TextileModel * TextileModel::createTextileModel( const Vector3D & p,     const Matrix3x3 & orientation,    Real width, Real height,    int rows, int cols){
  TextileModel * model = new TextileModel();

  model->buildModel(p,orientation,width,height,rows,cols);
  return model;
}
TextileNode* TextileModel::getNode(int i, int j){
  if(i<0)return 0;
  if(j<0)return 0;
  if(i>=_rows)return 0;
  if(j>=_columns)return 0;

  int index = i*_columns+j;
 
  return  _nodes.at(index);
}

void TextileModel::normalize(){

}
TextileModel::TextileModel(){}


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