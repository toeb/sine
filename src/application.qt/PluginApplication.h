#pragma once

#include <config.h>
#include <core/Set.h>
#include <application.qt/Plugin.h>
#include <application.qt/PluginContainer.h>
#include <core.hub/ModuleBase.h>

#include <QObject>
#include <QApplication>
#include <QMainWindow>

// forward declaration of plugin application main window
class Ui_PluginContainerWindow;
namespace nspace{
  class PluginApplication : public QObject, public virtual NamedObject,public virtual ModuleBase, public virtual ObservableCollection<Plugin*>::Observer{
    Q_OBJECT;
    TYPED_OBJECT;
  private:
    Set<Plugin*> _plugins;
    Set<Plugin*> _enabledPlugins;
    Set<Plugin*> _disabledPlugins;
  public:
    // all installed plugins will cause addition / removal will cause install / uninstall method to be called
    Set<Plugin*> & plugins();
    // uninstalls a plugin
    void uninstall(Plugin & plugin);
    //installs a plugin (and can also enable it)
    void install(Plugin & plugin, bool enable=true);
    // all enabled plugins
    const Set<Plugin * > & enabledPlugins()const;
    // all disabled plugins
    const Set<Plugin * > & disabledPlugins()const;
    // constructor needs the programs argument count as well as the argument vector
    PluginApplication(int & argc,  char ** argv);
    // executes this application
    int  run();
  protected slots:
    // called whenever a plugin was enabled or disabled
    void pluginEnabledChanged(PluginContainer * container, bool enabled=true);
    // closes this application
    void close();
  protected:
    // return true to add object to the module base' object set
    bool accept(Object * object);
    //returns the plugin container for the specified plugin.  if non exists it returns null
    PluginContainer * container(Plugin * plugin);
    // called when an plugin is added to the _plugins set
    void elementAdded(ObservableCollection<Plugin*> * sender, Plugin* element);
    // called when an plugin is removed to the _plugins set
    void elementRemoved(ObservableCollection<Plugin*> * sender, Plugin* element); 
    // rebuilds the main menu 
    void rebuildMenu();
    // rebuilds the window menu
    void rebuildWindowMenu();
    // friend class definition
    friend class PluginContainer;
  private:
    // connects the signal of a  plugin container
    void connectContainer(PluginContainer * c);
    // disconnects the signals of a plugin container
    void disconnectContainer(PluginContainer * c);
    
    Set<PluginContainer *> _containers;
    Ui_PluginContainerWindow * _ui;
    QMainWindow * _mainWindow;
    QApplication * _application;
  };

}