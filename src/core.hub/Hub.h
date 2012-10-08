#pragma once

#include <queue>
#include <stack>
#include <iostream>

#include <core/Set.h>
#include <core/NamedObject.h>
#include <core.hub/Module.h>
#include <core/StringTools.h>
#include <core/DataNode.h>
namespace nspace{

  typedef DataNode<Object*> HubNode;
  class Hub : 
    public virtual NamedObject , 
    public virtual Module, 
    public virtual HubNode,
    public virtual Set<Object*>
  {
    TYPED_OBJECT(Hub);
  private:
    Set<Module*> _modules;
    Set<Object *> _waitingAnnouncedObjects;
    Set<Object *> _waitingRenouncedObjects;
    bool _processing;
    

  public:
    



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