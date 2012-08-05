#pragma once
#include <visualization/core/Image.h>

namespace nspace{
class Texture : public virtual ISimulationObject{
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