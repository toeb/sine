#pragma once

#include <QGLWidget>

namespace nspace{
  class GlWidget : public QGLWidget{
    Q_OBJECT;

  public:


  protected:
  virtual void initializeGL();
  virtual void resizeGL(int w, int h);
  virtual void paintGL();
  };
}