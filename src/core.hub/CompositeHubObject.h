#pragma once

#include <core.hub/HubObject.h>


namespace nspace{
  
  class CompositeHubObject : public HubObject, private Set<Object*>,public virtual DataNode<Object*>{
    TYPED_OBJECT(CompositeHubObject);
  private:

  public:

    virtual void toString(std::ostream & out)const{
      out << "<CompositeHubObject components=\""<<size()<<"\" >"<<std::endl;
      
      foreachElement([&out](Object * object){
        out << " " ;
        std::string str = object->toString();
        
        str = std::extensions::replace(str,"\n","\n ");
        out << str<<std::endl;
      });      
      out <<"</CompositeHubObject>"<<std::endl;
    }
    CompositeHubObject():DataNode<Object*>(this){

    }
    ~CompositeHubObject(){
      // it does not seem to work
   /*   Set<Hub*> hubs = _hubs;
      Set<Object*> components = this->components();
      hubs.foreachElement([components](Hub * hub){
        
        *hub /= components;
       // *hub /= this;
      });*/
    }
    Set<Object*> & components(){
      return *this;
    }
  private:

    void onElementAdded(Object * object){
      _hubs.foreachElement([this,object](Hub * hub){
        *hub |= object;
      });
      onComponentAdded(object);

      auto node = dynamic_cast<DataNode<Object *> *>(object);
      if(!node){
        node = new DataNode<Object *>(object);
      }
      successors()|=node;
    }
    void onElementRemoved(Object * object){
      _hubs.foreachElement([this,object](Hub * hub){
        *hub /= object;
      });
      onComponentRemoved(object);

      auto element = successors().subset([object](DataNode<Object*> * node){
        return node->data() == object;
      });

      successors() /= element;



    }
  protected:
    virtual void onComponentAdded(Object * object){}
    virtual void onComponentRemoved(Object * object){}
    void onAddedToHub(Hub & hub){
      hub |= *this;
    }
    void onRemovedFromHub(Hub & hub){
      hub /= *this;
    }

  };

}