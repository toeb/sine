#pragma once

#include <core/NamedObject.h>
#include <core/Set.h>
#include <queue>
#include <core.hub/Module.h>
namespace nspace{


  

  class Hub : public virtual NamedObject , public virtual Module{
    TYPED_OBJECT;
  private:
    Set<Module*> _modules;
    Set<Object*> _objects;
    std::queue<Object *> _waitingAnnouncedObjects;
    std::queue<Object *> _waitingRenouncedObjects;
  public:
    Hub();    
    const Set<Module*> & modules()const;
    const Set<Object*> & objects()const;

    void announce(Object * object);
    void renounce(Object * object);
    

    Hub & operator << (Object * o);
    Hub & operator << (Object & o);


    void processObjects();
    void processObjectAnnounce(Object * object);
    void processObjectRenounce(Object * object);



  };
 

}