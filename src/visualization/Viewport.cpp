#include "Viewport.h"

using namespace nspace;



Real Viewport::aspectRatio()const {
  return (Real)_Width / (Real)_Height;
}
Viewport::Viewport():_ViewportRenderer(0),_Width(1),_Height(1){
  setName("Viewport");
}




void Viewport::propertyChanging(int,Width){
  
  doResize(getWidth(),getHeight());
}
void Viewport::propertyChanging(int,Height){
  if(newvalue<1)newvalue=1;
  doResize(getWidth(),getHeight());
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
