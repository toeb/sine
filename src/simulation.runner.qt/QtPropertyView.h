#pragma once
#include <QDockWidget>
#include <simulation/SimulationModuleBase.h>
#include <simulation.access/IValue.h>

class Ui_PropertyWindow;
namespace nspace{
  class QtPropertyView : public QDockWidget, public virtual SimulationModuleBase<IComponent>{
    Q_OBJECT;
  private:
    Ui_PropertyWindow * _ui;
  public:

  protected:
    void onObjectAdded(IComponent * component);
    void onObjectRemoved(IComponent * object);
  };
}