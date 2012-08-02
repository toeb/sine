
#include <QAction>

#include <simulation/access/IAction.h>

namespace nspace{
  class QtSimulationAction : public QAction{
    Q_OBJECT;
  private:
    IAction & _simulationAction;
  public:
    QtSimulationAction(IAction & action, QObject * parent = 0):
        QAction(QString::fromStdString(action.getName()),parent)
          ,_simulationAction(action){

          connect(this,SIGNAL(triggered()),this, SLOT(executeAction()));
    
    }
    public slots:
      void executeAction();


  };
};