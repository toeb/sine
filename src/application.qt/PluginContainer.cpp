#include "PluginContainer.h"
#include <application.qt/PluginApplication.h>
#include "ui_plugincontainer.h"
using namespace nspace;

// allows the plugin container to load its settings
void PluginContainer::loadSettings(QSettings & settings){
  settings.beginGroup(_plugin.name().c_str());

  if(_pluginWindow){
    auto mainWindow = application()._mainWindow;

    mainWindow->addDockWidget((Qt::DockWidgetArea)settings.value("dockarea", Qt::RightDockWidgetArea).toInt(), _pluginWindow);

    _pluginWindow->setFloating(settings.value("docked").toBool());
    auto size = settings.value("size", QSize(1, 1)).toSize();
    _pluginWindow->resize(size);
    _pluginWindow->move(settings.value("position", QPoint(200, 200)).toPoint());
  }
  _plugin.loadSettings(settings);
  settings.endGroup();
}
// allows the plugin container to save its settings
void PluginContainer::saveSettings(QSettings & settings){
  settings.beginGroup(_plugin.name().c_str());
  if(_pluginWindow){
    auto mainWindow = application()._mainWindow;

    settings.setValue("dockarea",  mainWindow->dockWidgetArea(_pluginWindow));
    settings.setValue("docked", _pluginWindow->isFloating());
    settings.setValue("size", _pluginWindow->size());
    settings.setValue("position", _pluginWindow->pos());
  }

  _plugin.saveSettings(settings);
  settings.endGroup();
}

PluginContainer::PluginContainer(Plugin & plugin, PluginApplication & app):_plugin(plugin),_pluginApplication(app),_pluginWindow(0),_pluginMenu(0),_togglePluginWindowAction(0){
  _enableDisableAction = new QAction(0);
  _enableDisableAction->setText(plugin.pluginName().c_str());
  _enableDisableAction->setCheckable(true);
  _enableDisableAction->setChecked(true);

  connect(_enableDisableAction,SIGNAL(toggled(bool)),this,SLOT(setEnabled(bool)));

  plugin.install(*this);
}

PluginContainer::~PluginContainer(){
  if(_togglePluginWindowAction){
    disconnect(_togglePluginWindowAction,SIGNAL(toggled(bool)),this,SLOT(setEnabled(bool)));
    delete _togglePluginWindowAction;
  }
  _plugin.uninstall(*this);
}
void PluginContainer::setEnabled(bool enabledFlag){
  if(enabledFlag){
    _plugin.enable();
    emit enabled(this);
  }
  else {
    _plugin.disable();
    emit disabled(this);
    toggleWindow(false);
  }

  emit enabledChanged(this,enabledFlag);
}
PluginApplication & PluginContainer::application(){
  return _pluginApplication;
}
Plugin & PluginContainer::plugin(){
  return _plugin;
}
QAction * PluginContainer::enableDisableAction(){
  return _enableDisableAction;
}
void PluginContainer::enable(){
  setEnabled(true);
}
PluginWindow * PluginContainer::pluginWindow(){
  return _pluginWindow;
}
void PluginContainer::setPluginWindow(PluginWindow * window){
  if(_pluginWindow){
    disconnect(_pluginWindow,SIGNAL(windowClosed()),this, SLOT(windowClosed()));
    _pluginApplication._mainWindow->removeDockWidget(_pluginWindow);
  }
  if(window==_pluginWindow)return;
  _pluginApplication.rebuildWindowMenu();
  _pluginWindow = window;
  if(_pluginWindow){
    connect(_pluginWindow,SIGNAL(windowClosed()),this, SLOT(windowClosed()));
    _pluginApplication._mainWindow->addDockWidget(Qt::LeftDockWidgetArea,_pluginWindow);
    _pluginWindow->setVisible(false);
    _pluginWindow->setObjectName(_plugin.name().c_str());
  }
}
QMenu * PluginContainer::pluginMenu(){
  return _pluginMenu;
}
QAction * PluginContainer::togglePluginWindowAction(){
  if(!_pluginWindow)return 0;
  if(!_togglePluginWindowAction){
    _togglePluginWindowAction = new QAction(0);
    _togglePluginWindowAction->setText(_plugin.pluginName().c_str());
    _togglePluginWindowAction->setCheckable(true);
    connect(_togglePluginWindowAction, SIGNAL(toggled(bool)),this, SLOT(toggleWindow(bool)));
  }
  return _togglePluginWindowAction;
}
void PluginContainer::uninstall(){
  application().uninstall(plugin());
}
void PluginContainer::disable(){
  setEnabled(false);
}

void PluginContainer::setPluginMenu(QMenu * menu){
  if(_pluginMenu == menu)return;
  _pluginMenu = menu;

  application().rebuildMenu();
}

void PluginContainer::toggleWindow(bool showFlag){
  auto window = pluginWindow();
  if(!window)return;
  window->setVisible(showFlag);
  togglePluginWindowAction()->setChecked(showFlag);
}

void PluginContainer::windowClosed(){
  toggleWindow(false);
}