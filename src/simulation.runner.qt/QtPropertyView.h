#pragma once
#include <QDockWidget>
#include <core.hub/ModuleBase.h>
#include <application.qt/Plugin.h>
#include <simulation.access/IValue.h>
class Ui_PropertyWindow;
namespace nspace{
  class QtPropertyView : public Plugin, public virtual TypedModuleBase<IComponent>{
    Q_OBJECT;
    TYPED_OBJECT(QtPropertyView);
  private:
    Ui_PropertyWindow * _ui;
  public:
    QtPropertyView();
    ~QtPropertyView();
  protected:
     void install(PluginContainer & container);
     void enable();
     void disable();
     void uninstall(PluginContainer & container);
     void loadSettings(QSettings & settings);
     void saveSettings(QSettings & settings);

    void onElementAdded(IComponent * component);
    void onElementRemoved(IComponent * component);
  };
}