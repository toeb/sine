#include "PluginApplication.h"

#include "ui_plugincontainer.h"

using namespace nspace;

Set<Plugin*> & PluginApplication::plugins(){return _plugins;}

PluginApplication::PluginApplication(int & argc,  char ** argv):
_ui(0),
  _mainWindow(0),
  _application(0),
 _settings("application.ini",QSettings::IniFormat)
{
  auto fn = _settings.fileName();
  
  _application = new QApplication(argc,argv);
  plugins().addObserver(this);

  _mainWindow = new QMainWindow();
  _ui = new Ui_PluginContainerWindow();
  _ui->setupUi(_mainWindow);
  _mainWindow->show();
  loadSettings();
  
  connect(_ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
  connect(_ui->actionLoadSettings,SIGNAL(triggered()),this,SLOT(loadSettings()));
  connect(_ui->actionSaveSettings,SIGNAL(triggered()),this,SLOT(saveSettings()));

}
int PluginApplication::run(){
  return _application->exec();
}
void PluginApplication::close(){
  _application->quit();
}
void PluginApplication::elementAdded(ObservableCollection<Plugin*> * sender, Plugin* plugin){
  auto container = this->container(plugin);
  if(!container)install(*plugin,true);
}

bool PluginApplication::accept(Object * object){
  auto plugin = dynamic_cast<Plugin*>(object);
  if(!plugin)return false;
  install(*plugin,true);
  return true;
}

void PluginApplication::saveSettings(){
   // store window layout
  _settings.beginGroup("MainWindow");
  _settings.setValue("geometry", _mainWindow->saveGeometry());
  //_settings.setValue("state", _mainWindow->saveState());
  _settings.endGroup();
  
  
  _containers.foreachElement([this](PluginContainer * container){
    savePluginSettings(container);
  });
  
}
void PluginApplication::loadSettings(){
    // load window layout
  _settings.beginGroup("MainWindow");
  _mainWindow->restoreGeometry(_settings.value("geometry").toByteArray());
 // _mainWindow->restoreState(_settings.value("state").toByteArray());
  _settings.endGroup();

  
  _containers.foreachElement([this](PluginContainer * container){
    loadPluginSettings( container);
  });


}


void PluginApplication::pluginEnabledChanged(PluginContainer * container, bool enabled){
  if(enabled){
    _disabledPlugins /= &container->plugin();
    _enabledPlugins |= &container->plugin();
  }else{
    _enabledPlugins /= &container->plugin();
    _disabledPlugins |= &container->plugin();
  }
  rebuildMenu();
  rebuildWindowMenu();
}
void PluginApplication::elementRemoved(ObservableCollection<Plugin*> * sender, Plugin* element){
  uninstall(*element);
} 
const Set<Plugin * > & PluginApplication::enabledPlugins()const{
  return _enabledPlugins;
}
const Set<Plugin * > & PluginApplication::disabledPlugins()const{
  return _disabledPlugins;
}
PluginContainer * PluginApplication::container(Plugin * plugin){
  return _containers.first([plugin](PluginContainer  * container){ return &container->plugin()==plugin; });
}
void PluginApplication::rebuildMenu(){
  _ui->menuBar->clear();
  _ui->menuBar->addMenu(_ui->menuFile);
  _ui->menuBar->addMenu(_ui->menuPlugins);
  _ui->menuBar->addMenu(_ui->menuWindows);

  enabledPlugins().foreachElement([this](Plugin * plugin){
    auto c = container(plugin);
    auto menu = c->pluginMenu();
    if(!menu)return;
    _ui->menuBar->addMenu(menu);
  });


  
}
void PluginApplication::rebuildWindowMenu(){
  _ui->menuWindows->clear();
  enabledPlugins().foreachElement([this](Plugin * plugin){
    auto c = container(plugin);
    auto window =  c->pluginWindow();
    if(!window)return;
    auto toggleWindowAction = c->togglePluginWindowAction();

    _ui->menuWindows->addAction(toggleWindowAction);
  
  });
}

void PluginApplication::savePluginSettings(PluginContainer * container){
  container->saveSettings(_settings);
}
void PluginApplication::loadPluginSettings(PluginContainer * container){
  container->loadSettings(_settings);
}

void PluginApplication::connectContainer(PluginContainer * c){  
  connect(c,SIGNAL(enabledChanged(PluginContainer * ,bool)),this,SLOT(pluginEnabledChanged(PluginContainer *, bool)) );

}
void PluginApplication::disconnectContainer(PluginContainer * c){
  disconnect(c,SIGNAL(enabledChanged(PluginContainer * ,bool)),this,SLOT(pluginEnabledChanged(PluginContainer *, bool)) );
}

void PluginApplication::uninstall(Plugin & plugin){
  auto container = this->container(&plugin);
  if(!container)return;
  container->disable();
  disconnectContainer(container);
  _ui->menuPlugins->removeAction(container->enableDisableAction());
  _containers /= container;
  _plugins.remove(&plugin);
  delete container;

}

void PluginApplication::onNameChanged(const std::string & name){
  if(_mainWindow)_mainWindow->setWindowTitle(name.c_str());
}

void PluginApplication::install(Plugin & plugin, bool enable ){
   // create a container for the added plugin
  PluginContainer * container = new PluginContainer(plugin,*this);  
  // add the plugin container to the containers set
  _containers |= container;
  // add action to plugin menu which can enable or disable it
  _ui->menuPlugins->addAction(container->enableDisableAction());
  connectContainer(container);
  _plugins|=(&plugin);
  if(enable)  container->enable();

  loadPluginSettings(container);

}