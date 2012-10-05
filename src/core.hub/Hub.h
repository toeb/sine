#pragma once

#include <queue>
#include <stack>

#include <core/Set.h>
#include <core/NamedObject.h>
#include <core.hub/Module.h>
#include <core/StringTools.h>
#include <core/DataNode.h>
namespace nspace{

  template<typename NodeType>
  class DepthFirstSearch{
    typedef Set<NodeType*> set;
    typedef std::function<void (NodeType * , set )> Action;
    typedef std::function<set  (const NodeType * ) > Successors; 
  public:
    inline static void operation(NodeType * node,  Action action, Successors successorFunction, set visited){
      action(node, visited);
      visited |= node;
      
      set successors = successorFunction(node);
      successors.foreachElement([successorFunction, visited, action](NodeType * child){
        DepthFirstSearch<NodeType>::operation(child,action,successorFunction,visited);
      });

    }
  };

  class Hub : 
    public virtual NamedObject , 
    public virtual Module, 
    public virtual DataNode<Object*>,
    public virtual Set<Object*>
  {
    TYPED_OBJECT(Hub);
  private:
    Set<Module*> _modules;
    Set<Object *> _waitingAnnouncedObjects;
    Set<Object *> _waitingRenouncedObjects;
    bool _processing;
    
  public:
    template<NodeType>
    void dfs(NodeType * node){
      
    }

    void toString(std::ostream & out)const{

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