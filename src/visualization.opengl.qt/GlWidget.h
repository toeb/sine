#pragma once
#include <config.h>
#include <QGLWidget>
#include <visualization.opengl/GlViewport.h>
#include <application.qt/QtInputHandler.h>
#include <core.hub/CompositeHubObject.h>
#include <visualization/ViewportController.h>
namespace nspace{
  class GlWidget : public QGLWidget, public virtual CompositeHubObject{
    Q_OBJECT;
    TYPED_OBJECT(GlWidget);
    GlViewport * _viewport;
    ViewportController * _viewportController;
    QtInputHandler _inputHandler;
  public:
    GlWidget(QWidget * parent=0);
    void setGlViewport(GlViewport * viewport);
    void setViewportController(ViewportController * controller);
    GlViewport * viewport();
  protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void onComponentAdded(Object * object);
    void onComponentRemoved(Object * object);

    
    void keyPressEvent(QKeyEvent* ke);
    void keyReleaseEvent(QKeyEvent* ke);
    void mouseMoveEvent(QMouseEvent* me);
    void mousePressEvent(QMouseEvent* me);
    void mouseReleaseEvent(QMouseEvent* me);
    bool eventFilter(QObject *object, QEvent *event);
  };
}