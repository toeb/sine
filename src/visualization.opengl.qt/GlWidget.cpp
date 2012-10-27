#include "GlWidget.h"
#include <QKeyEvent>

#define safe(x) if(x)x

using namespace nspace;
using namespace std;

GlWidget::GlWidget(QWidget * parent):QGLWidget(parent),
  _Viewport(0),
  _ViewportController(0),
  _inputHandler(0),
  _refreshTask([this](Time t, Time t2){repaint();})
{
  setName("GlWidget");
  _refreshTask.setIsOneTimeTask(false);
  _refreshTask.setInterval(0.01);
  _inputHandler=new QtInputHandler();
  Components()|=_inputHandler;
  Components()|=&_refreshTask;
  setFocusPolicy(Qt::StrongFocus);
  debugInfo("installing eventfilter and setting mouse tracking to true");
  installEventFilter(this);
  setMouseTracking(true);
}
void GlWidget::repaint(){
  updateGL();
}
void GlWidget::propertyChanging(ViewportController *, ViewportController){
  if(oldvalue){
    oldvalue->setViewport(0);
    Components()/=oldvalue;
  }
  if(newvalue){
    newvalue->setViewport(_Viewport);
    Components()|=newvalue; 
  }
}

void GlWidget::onComponentAdded(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(listener){
    _inputHandler->InputListeners()|=listener;
  }
}
void GlWidget::onComponentRemoved(Object * object){
  auto listener = dynamic_cast<IInputListener*>(object);
  if(listener){
    _inputHandler->InputListeners()/=listener;
  }
}

void GlWidget::propertyChanging(GlViewport *, Viewport){
  if(_ViewportController)_ViewportController->setViewport(newvalue);
}


void GlWidget::initializeGL(){
  auto view = getViewport();
  safe(view)->resize(QGLWidget::size().width(),  QGLWidget::size().height());
}
void GlWidget::resizeGL(int w, int h){

  auto view = getViewport();
  safe(view)->resize(w,h);
}
void GlWidget::paintGL(){
  auto view = getViewport();
  safe(view)->render();
}

void GlWidget:: mouseMoveEvent(QMouseEvent* me){
  // forward mouse event to input handler
  _inputHandler->mouseMoveEvent(me);
  debugMessage("mouse event "<<me->pos().x()<< " "<<me->pos().y(),6);
}

void GlWidget::mousePressEvent(QMouseEvent* me){
  // forward mouse event to input handler
  _inputHandler->mousePressEvent(me);
  debugMessage("mouse press "<<me->pos().x()<< " "<<me->pos().y(),6);
}

void GlWidget:: mouseReleaseEvent(QMouseEvent* me){
  // forward mouse event to input handler
  _inputHandler->mouseReleaseEvent(me);
  debugMessage("mouse release "<<me->pos().x()<< " "<<me->pos().y(),6);
}

void GlWidget:: keyReleaseEvent(QKeyEvent* me){
  // forward mouse event to input handler
  _inputHandler->keyReleaseEvent(me);
  debugMessage("key release "<<me->key(),6);
}

void GlWidget:: keyPressEvent(QKeyEvent* me){
  // forward mouse event to input handler
  _inputHandler->keyPressEvent(me);
  debugMessage("key press "<<me->key(),6);
}

bool GlWidget::eventFilter(QObject *object, QEvent *event)
{
  if(event->type()==QEvent::UpdateRequest){
    auto view = getViewport();
    safe(view)->resize(QGLWidget::size().width(),  QGLWidget::size().height());
  }
  return false;
}
