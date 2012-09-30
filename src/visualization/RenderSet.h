#pragma once

#include <core.hub/ModuleBase.h>
#include <visualization/IRenderer.h>

#include <functional>

namespace nspace{
  /**
  * \brief Render Module.
  *
  */
  class RenderSet:public virtual ModuleBase, public virtual IRenderer {
  private:
    Set<IRenderer*> _renderers;
  public:  
    void onBeforeRendering(Viewport & viewport){
      _renderers.foreachElement([&viewport](IRenderer * renderer){renderer->onBeforeRendering(viewport);});
    }
    void render(Viewport & viewport){
      _renderers.foreachElement([&viewport](IRenderer * renderer){renderer->render(viewport);});    
    }
    void sceneResized(int newWidth, int newHeight,Viewport & viewport){
      _renderers.foreachElement([&viewport, & newWidth,&newHeight](IRenderer * renderer){renderer->sceneResized(newWidth,newHeight,viewport);});    
    }

  };
}
