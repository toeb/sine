#pragma once
#include <config.h>
#include <QGLWidget>
#include <visualization.opengl/GlViewport.h>
#include <application.qt/QtInputHandler.h>
#include <core.hub/CompositeHubObject.h>
#include <core.task/ScheduledTaskDelegate.h>
#include <visualization/ViewportController.h>
#include <core.logging.h>
namespace nspace{
  class GlWidget : 
    public QGLWidget, 
    public virtual NamedObject, 
    public virtual CompositeHubObject,
    public virtual Log
  {
    Q_OBJECT;
    REFLECTABLE_OBJECT(GlWidget);
    SUBCLASSOF(Log);

    PROPERTY(GlViewport*, Viewport);
    PROPERTY(ViewportController*, ViewportController);

    QtInputHandler * _inputHandler;
    ScheduledTaskDelegate<> _refreshTask;

  public:
    GlWidget(QWidget * parent=0);
    void repaint();
  protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void onComponentAdded(Object * object);
    void onComponentRemoved(Object * object);
    
    bool eventFilter(QObject *object, QEvent *event);
    void keyPressEvent(QKeyEvent* ke);
    void keyReleaseEvent(QKeyEvent* ke);
    void mouseMoveEvent(QMouseEvent* me);
    void mousePressEvent(QMouseEvent* me);
    void mouseReleaseEvent(QMouseEvent* me);
  };
}
