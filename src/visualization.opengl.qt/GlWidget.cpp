#include "GlWidget.h"
#include <QKeyEvent>

#define safe(x) if(x)x

using namespace nspace;
using namespace std;

GlWidget::GlWidget(QWidget * parent):QGLWidget(parent),_viewport(0),_viewportController(0),
  _refreshTask([this](Time t, Time t2){repaint();}){
    _refreshTask.isOneTimeTask()=false;
    _refreshTask.interval()=0.01;
  components()|=&_inputHandler;
  components()|=&_refreshTask;
  setFocusPolicy(Qt::StrongFocus);
  installEventFilter(this);
}
void GlWidget::repaint(){
  updateGL();
}
void GlWidget::setViewportController(ViewportController * controller){
  components()/=controller;

  
  _viewportController = controller;

  
  safe(_viewportController)->setViewport(_viewport);
  components()|=controller;
}

void GlWidget::onComponentAdded(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(listener){
    this->_inputHandler.listeners()|=listener;
  }

  

}
void GlWidget::onComponentRemoved(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(listener){
    this->_inputHandler.listeners()/=listener;
  }
}

void GlWidget::setGlViewport(GlViewport * viewport){
  _viewport = viewport;
  safe(_viewportController)->setViewport(_viewport);
  safe(_viewportController)->setViewport(_viewport);
}
GlViewport * GlWidget::viewport(){return _viewport;}

void GlWidget::initializeGL(){
  auto view = viewport();
  //if(view)view->initialize();
}
void GlWidget::resizeGL(int w, int h){

  auto view = viewport();
  safe(view)->resize(w,h);
}
void GlWidget::paintGL(){
  auto view = viewport();
  safe(view)->render();
}

void GlWidget:: mouseMoveEvent(QMouseEvent* me){
  // forward mouse event to input handler
  _inputHandler.mouseMoveEvent(me);
}

void GlWidget::mousePressEvent(QMouseEvent* me){
  // forward mouse event to input handler
  _inputHandler.mousePressEvent(me);
}

void GlWidget:: mouseReleaseEvent(QMouseEvent* me){
  // forward mouse event to input handler
  _inputHandler.mouseReleaseEvent(me);
}

void GlWidget:: keyReleaseEvent(QKeyEvent* me){
  // forward mouse event to input handler
  _inputHandler.keyReleaseEvent(me);
}

void GlWidget:: keyPressEvent(QKeyEvent* me){
  // forward mouse event to input handler
  _inputHandler.keyPressEvent(me);
}

bool GlWidget::eventFilter(QObject *object, QEvent *event)
{
  switch(event->type()){
  case QEvent::FocusOut:

    break;
  case QEvent::FocusIn:

    break;
  }

  return false;
}
