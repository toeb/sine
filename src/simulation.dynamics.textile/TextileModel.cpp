#include "TextileModel.h"

#include <vector>
#include <algorithm>
#include <functional>

#include <simulation.dynamics/connection/ConnectorFactory.h>
#include <simulation.dynamics/connection/ParticleConnector.h>

using namespace std;
using namespace nspace;

Real TextileModel::getSuggestedStepSize()const{
  Real k=getElongationSpringConstant();
  if(k<getFlexionSpringConstant())k=getFlexionSpringConstant();
  if(k < getShearSpringConstant())k= getShearSpringConstant();
  int n= _rows*_columns;
  Real m_particle = _mass/n;
  Real T_0 = M_PI*sqrt(m_particle/k);
  return T_0;
}
void TextileModel::setMass(Real mass){
  _mass = mass;
  Real massPerNode = mass  /(_rows*_columns);
  for_each(_nodes.begin(), _nodes.end(), [massPerNode](TextileNode* node){
    if(!node->particle->isFixed())node->particle->setMass(massPerNode);
  });
}

Real TextileModel::getMass()const{
  return _mass;
}

/**
* \brief Normalizes a spring.
*
*
*
* \param [in,out] n1       the first TextileNode *.
* \param [in,out] n2       the second TextileNode *.
* \param [in,out] spring   the spring to be normalized.
* \param maxElongationRate The maximum elongation rate.
*/
inline void normalizeSpring(TextileNode * n1, TextileNode * n2, DampedSpring * spring, Real maxElongationRate){
  //calculate maximum elongation
  Real maxElongation = maxElongationRate * (spring->getRestLength());
  //calculate current elongation
  Real currentElongation = spring->getCurrentLength();

  //nothing to do if current elongation is smaller than maximum elongation
  if(currentElongation <= maxElongation)return;

  Particle *particle1 = n1->particle;
  Particle *particle2 = n2->particle;

  Vector3D pos1 = particle1->position();
  Vector3D pos2 = particle2->position();
  Vector3D normalizedElongationVector = (1 / currentElongation) * (pos2 - pos1);

  Vector3D offsetVector = (currentElongation - maxElongation) * normalizedElongationVector;

  Real mass1 = particle1->getMass();
  Real mass2 = particle2->getMass();

  //cases if particles are fixed / not fixed , not fixed / fixed and not fixed not fixed
  if (mass1 == 0 && mass2 != 0) {
    particle2->position() = pos2 - offsetVector;
  }
  else if (mass1 != 0 && mass2 == 0) {
    particle1->position() = pos1 + offsetVector;
  }
  else if (mass1 != 0 && mass2 != 0) {
    particle1->position() = pos1 + 0.5 * offsetVector;
    particle2->position() = pos2 - 0.5 * offsetVector;
  }
}
void TextileModel::normalize(){
  if(!isNormalizing())return;

  Real maxElongationRate = getMaximumElongation();
  normalizeEachSpring(maxElongationRate);
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
    // (rows ; cols) is in [3,n]x[3,n]
    if(rows < 0) rows = static_cast<int>(height);//set a row value corresponding to height
    if(rows < 3)  rows = 3;
    if(cols < 0) cols = static_cast<int>(width);//set a row value corresponding to width
    if(cols < 3) cols = 3;

    _rows = rows;
    _columns = cols;

    createNodeMesh(p,orientation);
    setMass(mass);
    setupNodeConnectivity();
    createSprings();
}

void TextileModel::normalizeEachSpring(Real maxElongationRate){
  //iterate through all springs
  for(int i =0; i < _rows; i++){
    for(int j =0; j < _rows; j++){
      TextileNode * n = getNode(i,j);
      //normalize each elongator and flexor if it is not null
      if(n->eastElongator){
        normalizeSpring(n,n->east,n->eastElongator,maxElongationRate);
      }
      if(n->southElongator){
        normalizeSpring(n,n->south,n->southElongator,maxElongationRate);
      }
      if(n->eastFlexor){
        normalizeSpring(n,n->east->east,n->eastFlexor,maxElongationRate);
      }
      if(n->southFlexor){
        normalizeSpring(n,n->south->south,n->southFlexor,maxElongationRate);
      }
      if(n->southEastShearer){
        normalizeSpring(n,n->east->south,n->southEastShearer,maxElongationRate);
      }
      if(n->southWestShearer){
        normalizeSpring(n,n->south->west,n->southWestShearer,maxElongationRate);
      }
    }
  }
}

void TextileModel::for_each_elongator(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f){
  for(int i =0; i < _rows; i++){
    for(int j =0; j < _rows; j++){
      TextileNode * n = getNode(i,j);
      if(n->eastElongator){
        f(n,n->east,n->eastElongator);
      }
      if(n->southElongator){
        f(n,n->south,n->southElongator);
      }
    }
  }
}
void TextileModel::for_each_flexor(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f){
  for(int i =0; i < _rows; i++){
    for(int j =0; j < _rows; j++){
      TextileNode * n = getNode(i,j);
      if(n->eastFlexor){
        f(n,n->east->east,n->eastFlexor);
      }
      if(n->southFlexor){
        f(n,n->south->south,n->southFlexor);
      }
    }
  }
}
void TextileModel::for_each_shearer(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f){
  for(int i =0; i < _rows; i++){
    for(int j =0; j < _rows; j++){
      TextileNode * n = getNode(i,j);
      if(n->southEastShearer){
        f(n,n->east->south,n->southEastShearer);
      }
      if(n->southWestShearer){
        f(n,n->south->west,n->southWestShearer);
      }
    }
  }
}

void TextileModel::for_each_spring(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f){
  for_each_elongator(f);
  for_each_flexor(f);
  for_each_shearer(f);
}

void TextileModel::addSimulationObject(ISimulationObject  * obj){
  _simulationObjects.push_back(obj);
}

Particle * TextileModel::createParticle(TextileNode * node, const Vector3D & position){
  Particle *p = node->particle;
  if(!p) {
    p = new Particle();

    node->particle = p;
    node->connector = (ParticleConnector*) ConnectorFactory::instance().createWithLocalConnectionPoint(*p,Vector3D::Zero());

    addSimulationObject(node->connector);
    //addSimulationObject(p);
  }
  p->position() = position;
  addSimulationObject(p);
  return p;
}

Real TextileModel::getMaximumElongation()const{
  return _maximumElongation;
}
void TextileModel::setMaximumElongation(Real value){
  _maximumElongation = value;
}
bool TextileModel::isNormalizing()const{
  return _normalize;
}
void TextileModel::setNormalizing(bool flag){
  _normalize = flag;
}
DampedSpring * TextileModel::createSpring(TextileNode * nodeA, TextileNode * nodeB, Real k_s, Real k_d){
  DynamicConnector* a = nodeA->connector;
  DynamicConnector * b = nodeB->connector;
  Real l_0 = (a->getWorldPosition()-b->getWorldPosition()).norm();
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
  //int n = _rows*_columns;
  //Real particleMass=_mass/n;

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
      node->i=i;
      node->j=j;
      _nodes.push_back( node);
      createParticle(node,position);
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

TextileModel::TextileModel():_maximumElongation(1.08), _normalize(true){}

void TextileModel::setElongationSpringConstant(Real k_s){
  _k_s_elongation = k_s;
  for_each_elongator([&k_s](TextileNode * n1, TextileNode * n2, DampedSpring * spring){
    spring->setStiffnessConstant(k_s);
  });
}
void TextileModel::setShearSpringConstant(Real k_s){
  _k_s_shear = k_s;
  for_each_shearer([&k_s](TextileNode * n1, TextileNode * n2, DampedSpring * spring){
    spring->setStiffnessConstant(k_s);
  });
}
void TextileModel::setFlexionSpringConstant(Real k_s){
  _k_s_flexion = k_s;
  for_each_flexor([&k_s](TextileNode * n1, TextileNode * n2, DampedSpring * spring){
    spring->setStiffnessConstant(k_s);
  });
}
void TextileModel::setElongationDampeningConstant(Real k_d){
  _k_d_elongation = k_d;

  for_each_elongator([&k_d](TextileNode * n1, TextileNode * n2, DampedSpring * spring){
    spring->setDampeningConstant(k_d);
  });
}
void TextileModel::setShearDampeningConstant(Real k_d){
  _k_d_shear = k_d;
  for_each_shearer([&k_d](TextileNode * n1, TextileNode * n2, DampedSpring * spring){
    spring->setDampeningConstant(k_d);
  });
}
void TextileModel::setFlexionDampeningConstant(Real k_d){
  _k_d_flexion = k_d;
  for_each_flexor([&k_d](TextileNode * n1, TextileNode * n2, DampedSpring * spring){
    spring->setDampeningConstant(k_d);
  });
}

void TextileModel::foreachNode(std::function<void (TextileNode* node)> f){
  for_each(_nodes.begin(), _nodes.end(), f);
}
Real TextileModel::getElongationSpringConstant()const{
  return _k_s_elongation;
}
Real TextileModel::getShearSpringConstant()const{
  return _k_s_shear;
}
Real TextileModel::getFlexionSpringConstant()const{
  return _k_s_flexion;
}
Real TextileModel::getElongationDampeningConstant()const{
  return _k_d_elongation;
}
Real TextileModel::getShearDampeningConstant()const{
  return _k_d_shear;
}
Real TextileModel::getFlexionDampeningConstant()const{
  return _k_d_flexion;
}