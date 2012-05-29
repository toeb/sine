#include "BoundingSphereTree.h"

using namespace IBDS;
using namespace std;


BoundingSphereHierarchy::BoundingSphereHierarchy(Geometry & obj):
leaf(true),
  _geometry(obj),
  level(0),
  nodeId(OctreeNodeId::NODE_ROOT){
  
}

BoundingSphereHierarchy::~BoundingSphereHierarchy(){
  if(isLeaf())return;
  setLeaf();
}

BoundingSphereHierarchy * BoundingSphereHierarchy::create(Geometry & geometry, int depth){
  BoundingSphereHierarchy * result = new BoundingSphereHierarchy(geometry);
  result->setPosition(geometry.getPosition());
  result->level = 0;
  result->setOrientation(geometry.getOrientation());
  result->setRadius(geometry.calculateBoundingSphereRadius());
  result->nodeId = OctreeNodeId::NODE_ROOT;
  
  result->refine(depth);
  return result;
}
 
void BoundingSphereHierarchy::set(BoundingSphereHierarchy * node){
  if(node!=0)leaf = false;
  BoundingSphereHierarchy * oldNode = _children[node->nodeId];
  if(oldNode)delete oldNode;
  _children[node->nodeId] = node;
}

void BoundingSphereHierarchy::refine(int depth){
  if(depth==0){
    setLeaf();
    return;
  };


  for(int i=0; i < 8; i++){    
     Real r = getRadius();
     Real r_new = 1.0/sqrt(2.0)* r;
     Real p_new = sqrt(r*r-r_new*r_new);
      Vector3D dir(-0.5,-0.5,-0.5);
      dir[0] += (i/4)%2;
      dir[1] += (i/2)%2;
      dir[2] += (i/1)%2;
      dir.normalize();      
      Vector3D newPosition = getPosition()+dir*p_new;

      BoundingSphereHierarchy * child = new BoundingSphereHierarchy(_geometry);
      child->level=level+1;
      child->nodeId = static_cast<OctreeNodeId>(i);
      child->setPosition(newPosition);
      child->setOrientation(getOrientation());
      child->setRadius(r_new);
     
   /*   if(!_geometry.boundaryIntersects(child->getPosition(),child->getRadius())){
        delete child;
        continue;
      }*/
      child->refine(depth-1);
      set(child);
  }
}

bool BoundingSphereHierarchy::allOnSameSide(){
  
  bool inside = false;
  bool outside = false;
  for_each_child([this,&inside,&outside](BoundingSphereHierarchy* h){
    if(_geometry.isInside(h->getPosition())){
      inside = true;
    }else{
      outside = true;
    }
  });
  if(inside&&outside)return false;
  else return true;
  
}

int BoundingSphereHierarchy::getLevel()const{
  return level;
}
bool BoundingSphereHierarchy::isLeaf()const{
  return leaf;
}
void BoundingSphereHierarchy::setLeaf(){
  leaf = true;
  for(int i=0; i < 8; i ++){
    delete (_children[static_cast<OctreeNodeId>(i)]);    
  }
  _children.clear();
}

BoundingSphereHierarchy * BoundingSphereHierarchy::get(OctreeNodeId node){
  if(leaf)return 0;
  return _children[node];
}

void BoundingSphereHierarchy::update(Real t, Real h){

}

void BoundingSphereHierarchy::for_each_child(std::function<void (BoundingSphereHierarchy*)> f){
  if(isLeaf())return;
  for(int i=0; i < 8; i++){
    BoundingSphereHierarchy * child = _children[static_cast<OctreeNodeId>(i)];
    if(!child)continue;
    f(child);
  }
}
void BoundingSphereHierarchy::for_each_in_level(int level, std::function<void (BoundingSphereHierarchy*)> f){
  if(level==0)f(this);
   
  if(isLeaf()) {
     return;
  }
  
  for(int i=0; i < 8; i++){
    BoundingSphereHierarchy * child =_children[static_cast<OctreeNodeId>(i)];
    if(!child)continue;
    child->for_each_in_level(level-1,f);
  }
}

void BoundingSphereHierarchy::for_each(std::function<void (BoundingSphereHierarchy*)> f){
  f(this);
  if(isLeaf()) {
     return;
  }
  
  for(int i=0; i < 8; i++){
    BoundingSphereHierarchy * child =_children[static_cast<OctreeNodeId>(i)];
    if(!child)continue;
    child->for_each(f);
  }
}