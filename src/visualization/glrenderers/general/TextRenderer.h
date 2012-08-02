#pragma once;
#include <visualization/core/IRenderer.h>
#include <visualization/opengl/MiniGL.h>

namespace nspace{
  
class TextRenderer : public IRenderer{
private:
  const std::string & _text;
  const char * _c_text;
  const Vector3D & _position;
  int _length;
  float _scale;
  const float * _color;
public:
  TextRenderer(const std::string & text, const Vector3D & position, const float * color =MiniGL::black, float scale=0.003);

  void render();
};

}