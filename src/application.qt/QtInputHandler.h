#pragma once

#include <simulation.interaction/InputHandler.h>
#include <core/PairMap.h>
#include <core/NamedObject.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <core.logging.h>
namespace nspace{
  // the qtinput handler translates key and mouse events from qt to the event system of dslib
  class QtInputHandler : public virtual InputHandler, public virtual NamedObject, public virtual Log{
    TYPED_OBJECT(QtInputHandler);
  private:
    PairMap<Qt::Key, nspace::Keys> _keys;
    PairMap<Qt::MouseButton, nspace::MouseButtons> _buttons;
  public:
    QtInputHandler();
  public:
    virtual void keyPressEvent(QKeyEvent* ke);
    virtual void keyReleaseEvent(QKeyEvent* ke);
    virtual void mouseMoveEvent(QMouseEvent* me);
    virtual void mousePressEvent(QMouseEvent* me);
    virtual void mouseReleaseEvent(QMouseEvent* me);
  };
}