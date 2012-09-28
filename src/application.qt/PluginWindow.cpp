#include "PluginWindow.h"
#include <QAction>

using namespace nspace;
using namespace std;


void PluginWindow::closeEvent(QCloseEvent * ev){
  emit windowClosed();
}

PluginWindow::PluginWindow(QWidget * parent):QDockWidget(parent){

}