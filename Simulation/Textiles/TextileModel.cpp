#include "TextileModel.h"
#include <algorithm>
#include <vector>
#include <Simulation/Dynamics/ParticleConnector.h>
#include <functional>
using namespace std;
using namespace IBDS;


void TextileModel::normalize(){

}


void TextileModel::buildModel(
  const Vector3D & p, 
  const Matrix3x3 & orientation,
  Real mass,
  Real width, Real height,
  int rows, int cols){
    
  _k_d_elongation=1;
  _k_s_elongation=10;
  _k_d_flexion=1;
  _k_s_flexion=10;
  _k_d_shear=1;
  _k_s_shear=10;


  _width = width;
  _height = height;
  _mass = mass;
  // (rows ; cols) is in [3,n]x[3,n]
  if(rows < 0) rows = static_cast<int>(height);//set a row value corresponding to height
  if(rows < 3)  rows = 3;
  if(cols < 0) cols = static_cast<int>(width);//set a row value corresponding to width
  if(cols < 3) cols = 3;
  
  _rows = rows;
  _columns = cols;
    
  createNodeMesh(p,orientation);   
  setupNodeConnectivity();
  createSprings();
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

vector<ISimulationObject*> & TextileModel::getSimulationObjects(){
  return _simulationObjects;
}

DampedSpring*  TextileModel::createFlexor(TextileNode * nodeA, TextileNode* nodeB){
  return createSpring(nodeA,nodeB,_k_s_flexion,_k_d_flexion);
}
DampedSpring*  TextileModel::createShearer(TextileNode * nodeA, TextileNode* nodeB){
  return createSpring(nodeA,nodeB,_k_s_shear,_k_d_shear);
}
DampedSpring* TextileModel::createElongator(TextileNode * nodeA, TextileNode* nodeB){
  return createSpring(nodeA,nodeB,_k_s_elongation,_k_d_elongation);
}

void TextileModel::createElongators(TextileNode * node){
  if(node->east){
    if(!node->eastElongator){
      DampedSpring * spring = createElongator(node,node->east);
      node->eastElongator = spring;
      node->east->westElongator = spring;
    }
  }

  if(node->north){
    if(!node->northElongator){
      DampedSpring * spring = createElongator(node,node->north);
      node->northElongator = spring;
      node->north->southElongator = spring;
    }
  }
}
void TextileModel::createShearers(TextileNode * node){
  if(node->east && node->east->north){
    if(!node->northEastShearer){
      DampedSpring * spring = createShearer(node,node->east->north);
      node->northEastShearer = spring;
      node->east->north->southWestShearer=spring;
    }
  }
  if(node->west && node->west->north){
    if(!node->northWestShearer){
      DampedSpring * spring = createShearer(node,node->west->north);
      node->northWestShearer = spring;
      node->west->north->southEastShearer = spring;
    }
  }
}
void TextileModel::createFlexors(TextileNode * node){
  if(node->east && node->east->east){
    if(!node->eastFlexor){
      DampedSpring * spring = createFlexor(node,node->east->east);
      node->eastFlexor = spring;
      node->east->east->westFlexor = spring;
    }
  }

  if(node->north && node->north->north){
    if(!node->northFlexor){
      DampedSpring * spring = createFlexor(node,node->north->north);
      node->northFlexor = spring;
      node->north->north->southFlexor= spring;
    }
  }
}

void TextileModel::createNodeMesh(const Vector3D & p, const Matrix3x3 & orientation){
  int n = _rows*_columns;
  Real particleMass=_mass/n;


  Real spacingWidth = _width/_columns;
  Real spacingHeight = _height/_rows;
  
  Vector3D x1(orientation(0,0),orientation(1,0), orientation(2,0));
  Vector3D x2(orientation(0,1),orientation(1,1), orientation(2,1));
  x1.normalize();
  x2.normalize();

  // create particles with correct mass and positions
  for(int i=0; i < _rows; i++){
    for(int j = 0; j < _columns;j++){
      Vector3D position = x1*spacingWidth*(i-_rows/2.0) + x2 * spacingHeight*(j-_columns/2.0) + p;
      TextileNode * node = new TextileNode();
      createParticle(node,particleMass,position);
      _nodes.push_back( node);
    }
  }
}
void TextileModel::setupNodeConnectivity(){  
  // set structure pointers
   for(int i=0; i < _rows; i++){
    for(int j = 0; j < _columns;j++){
        TextileNode * node = getNode(i,j);
        node->north = getNode(i-1,j);
        node->south = getNode(i+1,j);
        node->west =  getNode(i,j-1);
        node->east =  getNode(i,j+1);
    }
  }
}

void TextileModel::createSprings(){
  // create springs
  for(int i= 0; i < _rows; i++){
    for(int j=0; j < _columns; j++){      
      TextileNode * node = getNode(i,j);
      createFlexors(node);
      createShearers(node);
      createElongators(node);
    }
  }
}


TextileModel * TextileModel::createTextileModel( const Vector3D & p,     const Matrix3x3 & orientation, Real mass,   Real width, Real height,    int rows, int cols){
  TextileModel * model = new TextileModel();

  model->buildModel(p,orientation,mass,width,height,rows,cols);
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