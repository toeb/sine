#pragma once
#include <config.h>
#include <QGLWidget>
#include <visualization.opengl/GlViewport.h>
namespace nspace{
  class GlWidget : public QGLWidget{
    Q_OBJECT;
    GlViewport * _viewport;
  public:
    GlWidget(QWidget * parent=0);

    void setGlViewport(GlViewport * viewport);
    GlViewport * viewport();
  protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
  };
}