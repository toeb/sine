#include "TextRenderer.h"

using namespace std;
using namespace IBDS;

TextRenderer::TextRenderer(const std::string & text, const Vector3D & position, const float * color , float scale):
  _text(text),
  _position(position),
  _scale(scale),
  _color(color){}

void TextRenderer::render(){
  _c_text = _text.c_str();
  _length = _text.length();
  MiniGL::drawStrokeText(_position,_scale,_c_text,_length,_color);
}

