#include "CompositeHubObject.h"


using namespace nspace;


CompositeHubObject::CompositeHubObject(){
  data()=this;
}
CompositeHubObject::~CompositeHubObject(){
  // TODO remove components from hub without exceptions being thrown

}


void CompositeHubObject::itemAdded(Object*, Components){
  addObject(item);
  onComponentRemoved(item);
}
void CompositeHubObject::itemRemoved(Object *, Components){
  removeObject(item,true);
  onComponentAdded(item);
}
void CompositeHubObject::itemAdded(Object*, References){
  addObject(item);
  onReferenceAdded(item);
}
void CompositeHubObject::itemRemoved(Object *, References){
  removeObject(item,false);
  onReferenceRemoved(item);
}


void CompositeHubObject::addObject(Object * object){
  _hubs.foreachElement([this,object](Hub * hub){
    *hub |= object;
  });
  auto node = dynamic_cast<DataNode<Object *> *>(object);
  if(!node){
    node = new DataNode<Object *>(object);
  }
  successors()|=node;
  onObjectAdded(object);
}
void CompositeHubObject::removeObject(Object * object, bool fromHub){
  if(fromHub){
    _hubs.foreachElement([this,object](Hub * hub){
      *hub /= object;
    });
  }

  auto element = successors().subset([object](DataNode<Object*> * node){
    return node->data() == object;
  });
  // TODO delete ndoe if it was created in cho
  successors() /= element;
  onObjectRemoved(object);
}



void CompositeHubObject::onAddedToHub(Hub & hub){
  hub |= Components();
  hub |= References();
}
void CompositeHubObject::onRemovedFromHub(Hub & hub){
  hub /= Components();
  hub /= References();
}
