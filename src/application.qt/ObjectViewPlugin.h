#pragma once

#include <application.qt/Plugin.h>
#include <core/PropertyChangingObject.h>
#include <core/Reflection.h>
#include <application.qt/PluginWindow.h>
#include <core.hub/ModuleBase.h>
#include <QListWidgetItem>
#include <application.qt/ObjectPropertyView.h>
#include <core.logging.h>
class Ui_ObjectView;
namespace nspace{
  class ObjectViewPlugin : public Plugin, public virtual PropertyChangingObject, public virtual TypedModuleBase<Object>,public virtual Log {
    Q_OBJECT;    
    REFLECTABLE_OBJECT(ObjectViewPlugin);
    SUBCLASSOF(Log)
    PROPERTY(std::string,SearchString){
      debugMessage("SearchString changing to"<<newvalue,6);
    }
    PROPERTYSET(Object *, Objects,,)
  private:
    Ui_ObjectView * _ui;
    ObjectPropertyView * _objectPropertyView;
  public slots:
    void objectDoubleClicked(QListWidgetItem * object);
  public:
    ObjectViewPlugin():_ui(0),_SearchString(""){
      setName("ObjectViewPlugin");
    }
    void onPropertyChanged(const std::string & name);
    virtual void install(PluginContainer & container);
    virtual void enable(){}
    virtual void disable(){}
    virtual void uninstall(PluginContainer & container){}
    void updateObjectList();
    void updateListView();
    void onElementAdded(Object * object){
      updateObjectList();
    }
    void onElementRemoved(Object * object){
      updateObjectList();
    }
  };
}