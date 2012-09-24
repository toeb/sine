#include "SimulationDockWidget.h"
#include <QAction>

using namespace nspace;
using namespace std;


void SimulationDockWidget::closeEvent(QCloseEvent * ev){
  emit windowClosed();
}

SimulationDockWidget::SimulationDockWidget(QWidget * parent):QDockWidget(parent){

}