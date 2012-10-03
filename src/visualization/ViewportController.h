#pragma once
#include <core/Object.h>
#include <core/Set.h>

namespace nspace{
  class Viewport;
  class ViewportController : 
    public virtual Object,
    private Set<Viewport*>
  {
    TYPED_OBJECT(ViewportController);
  public:
    void setViewport(Viewport * viewport){
      Viewport * oldviewport = first();
      if(add(viewport)) remove(oldviewport);
    }
    
  protected:
    void onElementAdded(Viewport* viewport){onViewportAdded(viewport);}
    void onElementRemoved(Viewport* viewport){onViewportRemoved(viewport);}
    virtual void onViewportAdded(Viewport * viewport){}
    virtual void onViewportRemoved(Viewport * viewport){}

  };
}