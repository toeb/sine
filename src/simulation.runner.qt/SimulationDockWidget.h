#pragma once
#include <config.h>

#include <QDockWidget>

namespace nspace{


  class SimulationDockWidget : public QDockWidget{
    Q_OBJECT;
  private:
signals:
    void windowClosed();
  protected:
    void closeEvent(QCloseEvent * e);
  public:

    SimulationDockWidget(QWidget * parent=0);


  };

}