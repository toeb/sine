#pragma once
#include <visualization/Renderer.h>
#include <visualization/Light.h>
#include <core.logging.h>
#include <visualization/Material.h>
#include <visualization/Color.h>

#include <core/Set.h>
namespace nspace{

  class LightRenderer : 
    public virtual Renderer, 
    public virtual Log, 
    public virtual Set<Light*>,
    public virtual NamedObject
  {
    REFLECTABLE_OBJECT(LightRenderer);
    PROPERTY(Material,Material){}
    PROPERTY(Color,Color){setMaterial(Material(newvalue));}
    PROPERTY(bool,RenderLight){}
  public:
    LightRenderer(){setName("LightRenderer"); setColor(Color("green")); setRenderLight(true);}
    void doLights();
    void render();
    void onBeforeRendering();
  };
};