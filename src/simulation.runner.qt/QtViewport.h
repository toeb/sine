#pragma once

#include <application.qt/Plugin.h>
#include <visualization.opengl/GlViewport.h>
namespace nspace{
  class QtViewport : public Plugin{
    Q_OBJECT;
  private:
    GlViewport * _glViewport;
  public:
    QtViewport(){
      setName("QtViewport");
    }
  };
}