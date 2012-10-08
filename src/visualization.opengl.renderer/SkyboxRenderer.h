#pragma once

#include <visualization/Renderer.h>
#include <core.initialization/Initializable.h>
#include <core.hub/CompositeHubObject.h>
#include <visualization.opengl/GlTexture.h>
#include <core/Reflection.h>
#include <core/PropertyChangingObject.h>

#define PROP(TYPE,NAME) REFERENCE_PROPERTY(TYPE,NAME); REFLECTABLE_NOTIFYING_PROPERTY(TYPE,NAME)

namespace nspace{
  class SkyboxRenderer : 
    public virtual Renderer, 
    public virtual Initializable, 
    public virtual CompositeHubObject, 
    public virtual PropertyChangingObject,
    public virtual NamedObject{

    TYPED_OBJECT(SkyboxRenderer);
    REFLECTABLE(SkyboxRenderer);

    PROP(Set<Texture*>,Textures){}

  public:
    SkyboxRenderer(const std::string & filebase);
    void render();
  protected:
     void cleanupObject(){};
     bool initializeObject();
     
  };
}