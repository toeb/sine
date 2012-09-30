#pragma once

#include <utility.imaging/Image.h>
#include <core/NamedObject.h>
namespace nspace{
  class Texture : public virtual NamedObject{
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