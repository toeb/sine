#include "Viewport.h"

using namespace nspace;



Real Viewport::aspectRatio()const {
  return (Real)_width / (Real)_height;
}
Viewport::Viewport():_width(1),_height(1),_renderer(0),_controller(0){
  setName("Viewport");
}
void Viewport::setRenderer(Renderer * renderer){
  _renderer = renderer;
}

Renderer * Viewport::renderer(){
  return _renderer;
}
const Renderer * Viewport::renderer()const{
  return _renderer;
}
void Viewport::resize(int width, int height){
  if(width <=0)width = 1;
  if(height <= 0)height=1;

  if(_width==width && _height == height){
    return;
  }
  _width = width;
  _height = height;
  onResize(width,height);
  if(_renderer)_renderer->sceneResized(width,height,*this);
}
const int & Viewport::width()const{return _width;}
const int & Viewport::height()const{return _height;}

void Viewport::render(){
  onBeforeRender();
  if(!_renderer)return;
  _renderer->onBeforeRendering(*this);
  _renderer->render(*this);
  onAfterRender();
}
