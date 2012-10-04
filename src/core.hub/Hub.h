#pragma once

#include <queue>

#include <core/Set.h>
#include <core/NamedObject.h>
#include <core.hub/Module.h>
#include <core/StringTools.h>
#include <core/DataNode.h>
namespace nspace{
  class Hub : public virtual NamedObject , public virtual Module, public virtual DataNode<Object*>, public virtual Set<Object*>{
    TYPED_OBJECT(Hub);
  private:
    Set<Module*> _modules;
    Set<Object *> _waitingAnnouncedObjects;
    Set<Object *> _waitingRenouncedObjects;
    bool _processing;
    
  public:
    void toString(std::ostream & out)const{
      out << "<Hub name=\"" << name() <<"\">"<< std::endl;
      foreachElement([&out](Object * node){
        out << " " ;
        std::string str = node->toString();
        
        str = std::extensions::replace(str,"\n","\n ");
        out << str<<std::endl;
      });      
      out <<"</Hub>"<<std::endl;
    }

    Hub();    
    ~Hub();
    const Set<Module*> & modules()const;

    void announce(Object * object);
    void renounce(Object * object);

    // override
    virtual bool add(Object * element);
    virtual bool remove(Object * element);

    void processObjects();
    void processObjectAnnounce(Object * object);
    void processObjectRenounce(Object * object);

  protected:
    void onElementAdded(Object * object);
    void onElementRemoved(Object * object);

  };
}