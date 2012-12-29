#include "QtSnapshotControl.h"
#include "ui_statehistory.h"

using namespace nspace;
using namespace std;
class RecordTask:public virtual PeriodicTask{
private:
  QtSnapshotControl * _snapshotControl;

public:
  RecordTask(QtSnapshotControl * snapshotControl):PeriodicTask(10),_snapshotControl(snapshotControl){
  }
  virtual void timeout( Time timePassed,Time time )
  {
    if(_snapshotControl->isRecording())_snapshotControl->captureNow();
  }
};

QtSnapshotControl::QtSnapshotControl(QWidget * parent):
  _itemModel(0),
  _ui(0),
  _recordingTask(*new RecordTask(this)),
  _isRecording(false),
  _currentHistoryModule(0)
{
  _ui = new Ui_SnapshotControl();
  _itemModel = new QStandardItemModel(0,5);
  _ui->setupUi(this);
  _ui->snapshotsView->setModel(_itemModel);
  _ui->snapshotsView->header()->setResizeMode(QHeaderView::ResizeToContents);
  connect(_ui->createSnapshotButton, SIGNAL(clicked()), this, SLOT(captureNow()));
  connect(_ui->historyModule, SIGNAL(currentIndexChanged(int )), this, SLOT(moduleIndexChanged(int)));
  connect(_ui->loadCurrentState, SIGNAL(clicked()),this, SLOT(restoreSelectedSnapshot()));
  connect(_ui->storeStateAtButton, SIGNAL(clicked()),this, SLOT(captureAt()));
  connect(_ui->isRecordingCheckbox, SIGNAL(clicked(bool)), this, SLOT(setRecording(bool)));
  connect(_ui->snapshotsView,SIGNAL(doubleClicked(const QModelIndex & )),this,SLOT(snapshotDoubleClicked(const QModelIndex & )));
}
void QtSnapshotControl::snapshotDoubleClicked(const QModelIndex & itemIndex ){
  restoreSnapshot(itemIndex);
}
bool QtSnapshotControl::initializeObject(){
  *simulation()<<_recordingTask;
  return true;
}
void QtSnapshotControl::setRecording(bool value){
  Time t = QTime(0,0).msecsTo(_ui->recordRate->time())/1000.0;
  _recordingTask.interval()=t;
  _isRecording =value;
}
void QtSnapshotControl::moduleIndexChanged(int i){
  QVariant variant = _ui->historyModule->itemData(i);
  void * voidPtr = variant.value<void*>();
  HistoryModule * historyModule = static_cast<HistoryModule*>(voidPtr);
  _currentHistoryModule = historyModule;
  _itemModel->clear();

  QStringList list;
  list << "name"<<"time [simulation s]" << "datetime [real datetime]" <<"description";
  _itemModel->setHorizontalHeaderLabels(list);

  historyModule->foreachComponent([this](StateSnapshot * snapshot){
    addSnapshot(*snapshot);
  });
}

void QtSnapshotControl::restoreSnapshot(const QModelIndex & index){
  auto item = _itemModel->itemFromIndex(index);
  if(!item)return;
  auto variant = item->data();
  auto voidPtr = variant.value<void*>();
  auto snapshot = static_cast<StateSnapshot*>(voidPtr);
  if(!snapshot)return;
  _currentHistoryModule->restoreState(*snapshot);
}
void QtSnapshotControl::restoreSelectedSnapshot(){
  if(!_currentHistoryModule)return;
  auto selection= _ui->snapshotsView->selectionModel();

  if(!selection->hasSelection())return;
  auto indices=  selection->selectedIndexes();
  if(!indices.size())return;
  auto index = indices.first();
  restoreSnapshot(index);
}
void QtSnapshotControl::addSnapshot(StateSnapshot & snapshot){
  if(!_currentHistoryModule)return;
  QList<QStandardItem*> row;
  //row<<new QStandardItem();

  QStandardItem * root;

  root = new QStandardItem(QString::fromStdString(snapshot.name()));

  root->setData(qVariantFromValue<void*>(&snapshot));

  row<<root;

  stringstream ss;
  ss << snapshot.simulationTime();

  QStandardItem * current;
  current = new QStandardItem(QString::fromStdString(ss.str()));
  current->setData(qVariantFromValue<void*>(&snapshot));

  current->setEditable(false);

  row << current;
  auto datetime = QDateTime::fromMSecsSinceEpoch(snapshot.systemTime()*1000);
  QString time = datetime.toString(tr("dd.MM.yyyy hh.mm.ss"));
  current = new QStandardItem(time);
  current->setEditable(false);
  row << current;

  current =new QStandardItem(QString::fromStdString(snapshot.getDescription()));
  current->setEditable(false);
  row << current;
  /*
  root->appendRow(row);

  QList<QStandardItem*> l;
  l<<root;*/
  _itemModel->appendRow(row);
}
void QtSnapshotControl::captureNow(){
  if(!_currentHistoryModule)return;
  _currentHistoryModule->snapshot();
}
void QtSnapshotControl::captureAt(Time targetTime){
  if(!_currentHistoryModule)return;
  _currentHistoryModule->snapshotAt(targetTime);
}
void QtSnapshotControl::captureAt(){
  Time t = QTime().msecsTo(_ui->captureAtTimeEdit->time())/1000.0;
  captureAt(t);
}
void QtSnapshotControl::onPotentialSimulationObjectAdd(ISimulationObject * object){
  auto snapshot =  dynamic_cast<StateSnapshot*>(object);
  if(snapshot){
    if(&(snapshot->statefulObject())==&(_currentHistoryModule->statefulObject())){
      addSnapshot(*snapshot);
    }
  }
}

void QtSnapshotControl::recordCallback(Time actualTime){
  if(!_isRecording)return;
  captureNow();
}

void QtSnapshotControl::onObjectAdded(HistoryModule * historyModule){
  _ui->historyModule->addItem(QString::fromStdString(historyModule->name()), qVariantFromValue((void*)historyModule));
}
void QtSnapshotControl::onObjectRemoved(HistoryModule * historyModule){
}