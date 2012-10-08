#pragma once

#include <core.initialization/Initializable.h>
#include <utility.imaging/Image.h>
#include <core/NamedObject.h>
namespace nspace{
  class Texture : public virtual NamedObject, public virtual Initializable{
    TYPED_OBJECT(Texture);
  private:
    Image & _image;
    static uint _nextId;
    uint _id;
  public:
    Texture(Image & image);
    uint id()const;
    void bind()const;
    void unbind()const;
  protected:
    bool initializeObject();
  };
}