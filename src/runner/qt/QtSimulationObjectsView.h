#pragma once

#include <QDockWidget>

namespace mbslib{
  class QtSimulationObjectsView : public QDockWidget{
    Q_OBJECT;
  public:
    QtSimulationObjectsView(QWidget * parent);
  
  };

}