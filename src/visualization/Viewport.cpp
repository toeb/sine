#include "Viewport.h"

using namespace nspace;



Real Viewport::aspectRatio()const {
  return (Real)_Width / (Real)_Height;
}
Viewport::Viewport():_Width(1),_Height(1),_ViewportRenderer(0){
  setName("Viewport");
}




void Viewport::propertyChanging(int,Width){
  
  doResize(Width(),Height());
}
void Viewport::propertyChanging(int,Height){
  if(newvalue<1)newvalue=1;
  doResize(Width(),Height());
}
void Viewport::doResize(int width, int height){
  
  onResize(width,height);
  if(getViewportRenderer())getViewportRenderer()->sceneResized(width,height,*this);
}
void Viewport::resize(int width, int height){
  setWidth(width);
  setHeight(height);

}


void Viewport::render(){
  onBeforeRender();
  if(_ViewportRenderer)_ViewportRenderer->onBeforeRendering(*this);
  onBeginRender();
   if(_ViewportRenderer)_ViewportRenderer->render(*this);
  onAfterRender();
}
