#include "Octree.h"
#include <algorithm>
using namespace IBDS;
using namespace std;

void Octree::classify(){
  if(_depth==0)_classfication = classifyGeometrically();
  else _classfication = classifyByChildNodes();
}
Octree::~Octree(){
  delete _boundingVolume;
  _boundingVolume =0;
  
}
void Octree::createBoundingVolume(){
  _boundingVolume = _boundingVolumeFactory.create(getGeometry(),getAABB());
}

Octree *  Octree::createChild( OctreeNodeId id){
    Octree * child = new Octree(id, *this);
    child->_level = getLevel()+1;
    child->_depth =  _depth -1;

    // calculate the node bounding box
    child->_aabb.min = _aabb.min;
    child->_aabb.max = _aabb.max;
    Vector3D delta = 0.5*(_aabb.max - _aabb.min);
    if((id/4)%2==1){
      child->_aabb.min[0] += delta[0];
    }else{
      child->_aabb.max[0] -= delta[0];
    }
    if((id/2)%2==1){
      child->_aabb.min[1] += delta[1];
    }else{
      child->_aabb.max[1] -= delta[1];
    }
    if((id/1)%2==1){
      child->_aabb.min[2] += delta[2];
    }else{
      child->_aabb.max[2] -= delta[2];
    }
    
    child->createBoundingVolume();

    return child;
}


Octree::Octree(OctreeNodeId id, Octree & parent):
_geometry(parent.getGeometry()),
  _id(id),
  _children(0),
  _boundingVolumeFactory(parent._boundingVolumeFactory),
  _boundingVolume(0)
{
  _classfication = Classification::UNCLASSIFIED;
}
OctreeNodeId Octree::getId()const{
  return _id;
}

Octree * Octree::getNode(OctreeNodeId id){
  if(!_children)return 0;
  return _children[id];
}
void Octree::setNode(Octree * node){
  if(!_children){
    _children = new Octree*[8];
    for(int i=0; i < 8; i++){
      _children[i]=0;
    }
  }
  Octree * old = _children[node->getId()];
  if(old){
    old->deleteChildren();
    delete old;
  }
  _children[node->getId()]=node;
}

void Octree::deleteChildren(){
  if(_children){
    for(int i = 0; i < 8; i++){
      Octree * child = _children[i];
      if(!child) continue;
      child->deleteChildren();
      delete child;
      _children[i] =0;
    }
    delete _children;
    _children =0;
  }
}
Octree::Octree( Geometry & geometry,int depth, BoundingVolumeFactory & boundingVolumeFactory)
  :
_boundingVolume(0),
_boundingVolumeFactory(boundingVolumeFactory),
  _geometry(geometry),
  _id(OctreeNodeId::NODE_ROOT),
  _depth(depth),
  _level(0),
  _children(0){}

bool Octree::initializeObject(){
  cout<< "initializing octree for "<< *(_geometry.getName())<<endl;
  if( NODE_ROOT != _id)return true;
  deleteChildren();
  _geometry.initialize();
  _geometry.getBoundingBoxOCS(_aabb);
  refine();
  
  cout<< "done initializing octree for "<< *(_geometry.getName())<<endl;
  return true;
}
void Octree::cleanupObject(){
  if( NODE_ROOT != _id)return;
  deleteChildren();
}

unsigned int Octree::getLevel()const{
  return _level;
}
Classification Octree::getClassification()const{
  return _classfication;
}
bool Octree::isLeaf()const {
  // octree is a leaf if it has no children
  if(_children)return false;
  return true;
}
Geometry & Octree::getGeometry()const{
  return _geometry;
}
void Octree::getCenter(Vector3D & c_ocs)const{
  c_ocs.assign(_aabb.min+0.5*(_aabb.max - _aabb.min));
}
Classification Octree::classifyGeometrically()const{
  Vector3D center;
  _aabb.getCenter(center);
  Real radius;
  radius = (_aabb.min-_aabb.max).length();
  return _geometry.classify(center,radius);
}
Classification Octree::classifyByChildNodes()const{
  // classifies by child nodes.  if all nodes are inside it returns inside
  //if all nodes are otuside it returns outside
  // if there is a child which is inside and another which is outside it returns both
  // if this is a leaf it returns outside.  classifiying by child nodes when node is a leaf is an undefined 
  // process

  Classification result = Classification::OUTSIDE;
  if(isLeaf()){
    return result;
  }
  int numberOfChildren=0;
  for(int i =0; i < 8; i++){
    Octree * child = _children[i];
    if(!child){
     result = static_cast<Classification>(result | Classification::OUTSIDE); 
    }else{
      result = static_cast<Classification>(result | child->getClassification());
      numberOfChildren++;
    }
    if(result==Classification::BOTH)return result;
  }
  if(numberOfChildren != 8)result = static_cast<Classification>(result | Classification::OUTSIDE);
  return result;
}

const AABB & Octree::getAABB()const{
  // returns the dimesion of the octree in AABB ocs format
  return _aabb;
}

void Octree::refine(){
  // if finest level is not yet reached
  // recurse until it is.
  if(getDepth() > 0 ){
    for(int i = 0; i <  8;  i++){
      // create and refine all 8 child nodes
      Octree * child =createChild(static_cast<OctreeNodeId>(i));
      child->refine();
      // if child is outside then throw it away
      if(child->getClassification()==Classification::OUTSIDE)
        delete child;
      else  
        setNode(child); // else save it
    }
  }
  // classify the current node 
  classify();
  // if if the node is classified as inside or outside delete all children
  switch(getClassification()){
    case Classification::INSIDE:
    case Classification::OUTSIDE:
      deleteChildren();
     
      break;
  }
  //calulate the new depth of this node (it is the max(depth(child))+1
  int d = -1;
  foreachChild([&d](Octree * child){
    if(d < child->getDepth())d = child->getDepth();
  });
  _depth = static_cast<unsigned int>(d+1);
}

unsigned int Octree::getDepth()const{
  return _depth;
}



/** Iterators **/

void Octree::foreachChildOfLevel(unsigned int level, std::function<void (Octree*)> f){
  if(getLevel()==level){
    f(this);
    return;
  }
  foreachChild([&level, &f](Octree * child){
    child->foreachChildOfLevel(level, f);
  });
}
void Octree::foreach(std::function<void (Octree*)> f){
  if(isLeaf()){
    f(this);
    return;
  }
  foreachChild([&f](Octree * child){
    child->foreachChild(f);
  });
}

void Octree::foreachLeaf(std::function<void (Octree*)> f){
  foreach([&f](Octree * child){
    if(child->isLeaf())f(child);
  });
}

void Octree::foreachChild(function<void (Octree*)> f){
  if(!_children)return;
  for(int i=0; i < 8; i ++){
    Octree * child = _children[i];
    if(!child)continue;
    f(child);
  }
}