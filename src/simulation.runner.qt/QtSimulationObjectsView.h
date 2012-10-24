#pragma once

#include <application.qt/Plugin.h>
#include <application.qt/PluginWindow.h>
#include <application.qt/PluginContainer.h>
#include <core/Reflection.h>

namespace nspace{
  class QtObjectViewPlugin : public Plugin{
    Q_OBJECT;
    REFLECTABLE_OBJECT(QtObjectViewPlugin);
    
  public:
    QtObjectViewPlugin(){
    
    }


  
  };

}