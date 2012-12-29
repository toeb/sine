#pragma once

#include <config.h>
#include <core/Object.h>
#include <QObject>
#include <application.qt/Plugin.h>
#include <application.qt/PluginWindow.h>
#include <QMenu>
#include <QAction>
#include <QSettings>
namespace nspace{
  class PluginApplication;
  class PluginContainer : public QObject, public virtual Object{
    Q_OBJECT;
    TYPED_OBJECT(PluginContainer);
  private:
    // reference to the plugin
    Plugin & _plugin;
    // reference to the plugin application
    PluginApplication & _pluginApplication;
    // pointer to the plugin window
    PluginWindow * _pluginWindow;
    //pointer to the plugin's menu
    QMenu * _pluginMenu;
  public:
    // allows the plugin container to load its settings
    void loadSettings(QSettings & settings);
    // allows the plugin container to save its settings
    void saveSettings(QSettings & settings);
    // constructor takes a reference to the plugin and the plugin application
    PluginContainer(Plugin & plugin, PluginApplication & application);
    // destructor
    ~PluginContainer();
    // returns reference to the plugin application
    PluginApplication & application();
    // returns a reference to the contained plugin
    Plugin & plugin();
    //returns the pointer to the enable disable action
    QAction * enableDisableAction();
    // returns a pointer to the togglewindow action if the window exists else null
    QAction * togglePluginWindowAction();
    // returns a pointer to a menu if set or null
    QMenu * pluginMenu();
    // returns a pointer to the plugin window
    PluginWindow * pluginWindow();
    // set the plugin's window
    void setPluginWindow(PluginWindow * window);
    // sets the plugin's menu
    void setPluginMenu(QMenu * menu);
signals:
    // signal is emitted  when this container's plugin is enabled
    void enabled(PluginContainer * container);
    // signal is emitted when this containers's plugin is disabled
    void disabled(PluginContainer * container);
    // signal is emitted when the enabled state is changed
    void enabledChanged(PluginContainer * container, bool isEnabled);
    public slots:
      // uninstalls this plugin from its plugin application
      void uninstall();
      // enables the plugin
      void enable();
      // disables the plugin
      void disable();
      // sets the plugin to enabled or disabled
      void setEnabled(bool enabledDisabled);
      // toggles the window of the plugin if it exists
      void toggleWindow(bool show);
      // called when plugin window is closed
      void windowClosed();
  private:
    // enableDisable action
    QAction * _enableDisableAction;
    // toggles the windows visibility
    QAction * _togglePluginWindowAction;
    // friend class definition
    friend class PluginApplication;
  };
}