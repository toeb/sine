#pragma once

#include <core.hub/ModuleBase.h>
#include <visualization/Renderer.h>

#include <functional>

namespace nspace{
  /**
  * \brief Render Module.
  *
  */
  class RenderSet:public virtual TypedModuleBase<Renderer>, public virtual Renderer {
    TYPED_OBJECT(RenderSet);
  private:
    
  public:  
    void onBeforeRendering(Viewport & viewport){
      foreachElement([&viewport](Renderer * renderer){renderer->onBeforeRendering(viewport);});
    }
    void render(Viewport & viewport){
      foreachElement([&viewport](Renderer * renderer){renderer->render(viewport);});    
    }
    void sceneResized(int newWidth, int newHeight,Viewport & viewport){
      foreachElement([&viewport, & newWidth,&newHeight](Renderer * renderer){renderer->sceneResized(newWidth,newHeight,viewport);});    
    }

  };
}
