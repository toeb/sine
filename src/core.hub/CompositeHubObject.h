#pragma once

#include <core.hub/HubObject.h>


namespace nspace{
  
  class CompositeHubObject : public HubObject, private Set<Object*>{
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
    CompositeHubObject(){

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
    }
    void onElementRemoved(Object * object){
      _hubs.foreachElement([this,object](Hub * hub){
        *hub /= object;
      });
      onComponentRemoved(object);
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