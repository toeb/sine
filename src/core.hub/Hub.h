#pragma once

#include <queue>
#include <stack>

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


    void toString(std::ostream & out)const{
      typedef HubNode* node;
      typedef Set<node> set;

      set visited;
      set unexplored;
      set path;

      unexplored |= successors();

      while(unexplored){
        node current = unexplored.last();
        unexplored /= current;
        if(visited.contains(current))continue;
        visited |= current;
        
        std::cout << "."<<std::endl;

      }



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