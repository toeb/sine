#include <application.qt.h>

using namespace nspace;
int main(int argc, char** argv){
  // create the application object
  PluginApplication app(argc,argv);

  // add a sample plugin
  auto plugin = new Plugin();
  plugin->setName("Sample Plugin");
  app.plugins().add(plugin);

  // run the application
  return app.run();


}