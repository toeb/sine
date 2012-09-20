#pragma once

#include <QDockWidget>
#include <core/Time.h>
#include <simulation.history/HistoryModule.h>
#include <simulation/SimulationModuleBase.h>
#include <QStandardItemModel>
#include <QStandardItem>
class Ui_SnapshotControl;

namespace nspace{
  class QtSnapshotControl : public QDockWidget, public virtual SimulationModuleBase<HistoryModule>{
    Q_OBJECT;
  public:
    QtSnapshotControl(QWidget * parent);
    bool isRecording()const{return _isRecording;}
  protected:
    void onObjectAdded(HistoryModule * historyModule);
    void onObjectRemoved(HistoryModule * historyModule);
    void onPotentialSimulationObjectAdd(ISimulationObject * object);
    
  public slots:
    void restoreSelectedSnapshot();
    void captureNow();
    void captureAt();
    void captureAt(Time targetTime);
    void moduleIndexChanged(int i);
    void setRecording(bool value);
    void snapshotDoubleClicked(const QModelIndex & index );
    void restoreSnapshot(const QModelIndex &);

  protected:
    bool initializeObject();
  private:
    void recordCallback(Time actualTime);

    void addSnapshot(StateSnapshot & snapshot);
    QStandardItemModel * _itemModel;
    Ui_SnapshotControl * _ui;
    PeriodicTask & _recordingTask;
    bool _isRecording;
    HistoryModule * _currentHistoryModule;
  };

}