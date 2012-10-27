#pragma once
#include <QDockWidget>
#include <core.hub/ModuleBase.h>
#include <application.qt/Plugin.h>
#include <core/Reflection.h>
#include <core.logging.h>
#include <simulation.access/IValue.h>


#include <QStandardItem>
#include <QStandardItemModel>

class Ui_PropertyWindow;
namespace nspace{
  class ValueItem;
  class QtPropertyView : 
    public Plugin, 
    public virtual TypedModuleBase<IComponent>,
    public virtual Log
  {
    Q_OBJECT;
    REFLECTABLE_OBJECT(QtPropertyView);
    // Refresh rate in hz
    PROPERTY(int, RefreshRate);
    PROPERTYSET(ValueItem*,ValueItems,,);
  private:
    Ui_PropertyWindow * _ui;
    QStandardItem * _rootNode;
    QStandardItemModel * _itemModel;
    QTimer * _refreshTimer;
  public:
    QtPropertyView();
    ~QtPropertyView();
    public slots:
      void refreshProperties();
  protected:
     void install(PluginContainer & container);
     void enable();
     void disable();
     void uninstall(PluginContainer & container);
     void loadSettings(QSettings & settings);
     void saveSettings(QSettings & settings);

    void onElementAdded(IComponent * component);
    void onElementRemoved(IComponent * component);
  private:
    void updateTimer(int refreshrate);
  };
}