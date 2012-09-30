#include "GlWidget.h"

using namespace nspace;

GlWidget::GlWidget(QWidget * parent):QGLWidget(parent),_viewport(0){}

void GlWidget::setGlViewport(GlViewport * viewport){_viewport = viewport;}
GlViewport * GlWidget::viewport(){return _viewport;}

void GlWidget::initializeGL(){
}
void GlWidget::resizeGL(int w, int h){
}
void GlWidget::paintGL(){
  auto view = viewport();
  if(view)view->render();
}