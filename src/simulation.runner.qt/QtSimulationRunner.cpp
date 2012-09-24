/*
 * Copyright (C) 2011
 * Simulation, Systems Optimization and Robotics Group (SIM)
 * Technische Universitaet Darmstadt
 * Hochschulstr. 10
 * 64289 Darmstadt, Germany
 * www.sim.tu-darmstadt.de
 *
 * This file is part of the mbslib.
 * All rights are reserved by the copyright holder.
 *
 * The mbslib is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You may use the mbslib or parts of it only with the written permission of the copyright holder.
 * You may NOT modify or redistribute any part of the mbslib without the prior written
 * permission by the copyright holder.
 *
 * Any violation of the rights and restrictions mentioned above will be prosecuted by civil and penal law.
 * Any expenses associated with the prosecution will be charged against the violator.
 */

/**
 * \file src/vis/qt_model_viewer/QtModelViewer.cpp
 * 
 */
#include <iostream>
#include <algorithm>

#include <simulation.access/IValue.h>

#include <simulation.history/HistoryModule.h>

#include <visualization.opengl/FpsCamera.h>

#include <simulation.runner.qt/ValueItemFactory.h>
#include <simulation.runner.qt/ValueItemDelegate.h>
#include <simulation.runner.qt/QtSimulationAction.h>

#include <QApplication>
#include <QDockWidget>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QListView>
#include <QTreeView>
#include <QStandardItemModel>

#include "ui_mainwindow.h"
#include "ui_propertyWindow.h"

#include "QtSimulationRunner.h"

using namespace nspace;
using namespace std;
void QtSimulationRunner::onSimulationSet(){
	
}


QtSimulationRunner::QtSimulationRunner( int _argc, char** _argv, bool startPaused):
  _realTimeModule(0),propertyUi(0),_timeControl(0),
 settings(QSettings::IniFormat, QSettings::UserScope, "sim.tu-darmstadt.de", "QtSimulationRunner")
 ,argc(*(new int(_argc)))
 ,argv(_argv)
{
  setName("QtSimulationRunner");
  
}



QtSimulationRunner::~QtSimulationRunner(){}

void QtSimulationRunner::wireframe(bool on){
  if(on) 
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  else {
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
  }
}


void QtSimulationRunner::saveWindowState()
{
  // store window layout
  settings.beginGroup("MainWindow");
  settings.setValue("geometry", mainWindow->saveGeometry());
  settings.setValue("state", mainWindow->saveState());
  settings.endGroup();
  //store camera settings
  settings.beginGroup("Camera");

   auto viewport = dynamic_cast<ViewportBase*>(glWidget->viewport());

  if(viewport){
    
    stringstream ss;
    
    ss<<viewport->coordinates().position()(0);
    ss<<viewport->coordinates().position()(1);
    ss<<viewport->coordinates().position()(2);
    ss<<viewport->coordinates().orientation().x();
    ss<<viewport->coordinates().orientation().y();
    ss<<viewport->coordinates().orientation().z();
    ss<<viewport->coordinates().orientation().w();
    settings.setValue("camera", QString::fromStdString(ss.str()));
  }
  settings.endGroup();
}

void QtSimulationRunner::loadWindowState()
{
  // load window layout
  settings.beginGroup("MainWindow");
  mainWindow->restoreGeometry(settings.value("geometry").toByteArray());
  mainWindow->restoreState(settings.value("state").toByteArray());
  settings.endGroup();
  // load camera settings  
  settings.beginGroup("Camera");
  //camera.loadState(settings.value("camera").toString().toStdString());

  auto viewport = dynamic_cast<ViewportBase*>(glWidget->viewport());
  
   auto val= settings.value("camera");
   auto qstr = val.toString();    
   const QByteArray asc = qstr.toAscii();
   string str(asc.constData(), asc.length());
   
  if(viewport){
    stringstream ss(str);
    if(str.length()>0){
      ss>>viewport->coordinates().position()(0);
      ss>>viewport->coordinates().position()(1);
      ss>>viewport->coordinates().position()(2);
      ss>>viewport->coordinates().orientation().x();
      ss>>viewport->coordinates().orientation().y();
      ss>>viewport->coordinates().orientation().z();
      ss>>viewport->coordinates().orientation().w();
    }
  }

  settings.endGroup();
}


void QtSimulationRunner::showRenderWindow(bool visible){
  renderWindow->setVisible(visible);
}
void QtSimulationRunner::showTimeWindow(bool visible){}
void QtSimulationRunner::showHistoryWindow(bool visible){}
void QtSimulationRunner::showPropertiesWindow(bool visible){}
bool QtSimulationRunner::initializeRunner(){              
  application = new QApplication(argc,argv);
    
  // setup main window
  mainWindow=new QMainWindow();
  ui = new Ui_MainWindow();
  ui->setupUi(mainWindow);
  mainWindow->show();
                                                      
  // setup render window
  glWidget = new GlWidget(mainWindow);
	
	//create default viewport
  auto fpsCam = new FpsCamera();
	Viewport * viewport =fpsCam;
  HistoryModule * cameraHistory = new HistoryModule(fpsCam->kinematicBody(),*new SimulationTimeProvider());
  cameraHistory->setName("Camera Position History");
  simulation()->add(cameraHistory);
	glWidget->setViewport(viewport);


renderWindow = new SimulationDockWidget();
  renderWindow->setObjectName(("RenderWindow"));
  renderWindow->setWidget(glWidget);
  mainWindow->addDockWidget(Qt::LeftDockWidgetArea,renderWindow);
  
  QAction * renderWindowAction = new QAction("Render Window",0);
  renderWindowAction->setCheckable(true);
  renderWindowAction->setChecked(true);  
  connect(renderWindow, SIGNAL(windowClosed()), renderWindowAction, SLOT(toggle()));
  connect(renderWindowAction,SIGNAL(triggered(bool)),this,SLOT(showRenderWindow(bool)));  
  ui->menuWindows->addAction(renderWindowAction);
  

	
	// add the render engine to the simulation
	simulation()->add(glWidget);
	simulation()->add(&(glWidget->inputHandler()));
	simulation()->add(viewport);

  //setup time controller

  
  _timeControl =  new QtTimeControl();
  mainWindow->addDockWidget(Qt::TopDockWidgetArea,_timeControl);

  //setup history 
  _snapshotControl = new QtSnapshotControl(0);
  mainWindow->addDockWidget(Qt::BottomDockWidgetArea,_snapshotControl);

    QAction * timeControlWindowAction = new QAction("Time Control Window",0);
  timeControlWindowAction->setCheckable(true);
  timeControlWindowAction->setChecked(true);  
  connect(_timeControl, SIGNAL(windowClosed()), timeControlWindowAction, SLOT(toggle()));  
  connect(timeControlWindowAction,SIGNAL(triggered(bool)),_timeControl,SLOT(setVisible(bool)));  
  ui->menuWindows->addAction(timeControlWindowAction);

  // history
   _snapshotControl = new QtSnapshotControl(0);
  mainWindow->addDockWidget(Qt::BottomDockWidgetArea,_snapshotControl);
 *simulation()<<_snapshotControl;

  QAction * snapshotWindowAction = new QAction("Snapshot Window",0);
  snapshotWindowAction->setCheckable(true);
  snapshotWindowAction->setChecked(true);  
  connect(_snapshotControl, SIGNAL(windowClosed()), snapshotWindowAction, SLOT(toggle()));  
  connect(snapshotWindowAction,SIGNAL(triggered(bool)),_snapshotControl,SLOT(setVisible(bool)));  
  ui->menuWindows->addAction(snapshotWindowAction);


 // Setup Property Window
 propertyWindow = new SimulationDockWidget();
  propertyWindow->setObjectName("PropertyWindow");
  Ui_PropertyWindow * propertyUi = new Ui_PropertyWindow();
  propertyUi->setupUi(propertyWindow);
  mainWindow->addDockWidget(Qt::RightDockWidgetArea, propertyWindow);

  QAction * propertyWindowAction = new QAction("Property Window",0);
  propertyWindowAction->setCheckable(true);
  propertyWindowAction->setChecked(true);  
  connect(propertyWindow, SIGNAL(windowClosed()), propertyWindowAction, SLOT(toggle()));  
  connect(propertyWindowAction,SIGNAL(triggered(bool)),propertyWindow,SLOT(setVisible(bool)));  
  ui->menuWindows->addAction(propertyWindowAction);


  _itemModel = new QStandardItemModel;
  _itemModel->setColumnCount(10);
  _rootNode= _itemModel->invisibleRootItem();

  propertyUi->treeView->setItemDelegate(new ValueItemDelegate());
  propertyUi->treeView->setModel(_itemModel);
  propertyUi->treeView->header()->setResizeMode(QHeaderView::ResizeToContents);
  

  //if(propertyUi)propertyUi->treeView->header()->resizeSections(QHeaderView::ResizeToContents);

  //register actions
  connect(ui->actionWireframe, SIGNAL(toggled(bool)),this, SLOT(wireframe(bool)));  
  connect(ui->actionSaveSettings, SIGNAL(triggered()), this, SLOT(saveWindowState()));  
  connect(ui->actionTogglePause, SIGNAL(triggered()), this, SLOT(togglePause()));
  connect(ui->actionStep, SIGNAL(triggered()),this,SLOT(step()));  
  connect(ui->actionGrabFrame, SIGNAL(triggered()),glWidget,SLOT(captureOnce()));
  connect(ui->actionStoreSequence, SIGNAL(triggered()), glWidget,SLOT(storeSequence()));
  connect(ui->actionClearSequence, SIGNAL(triggered()), glWidget, SLOT(clearSequence()));
  connect(ui->actionToggleCapture, SIGNAL(triggered()), glWidget, SLOT(toggleCapture()));
  connect(ui->actionSet_Framerate,SIGNAL(triggered()),glWidget,SLOT(setFramerate()));
  connect(ui->actionSet_Capture_Rate,SIGNAL(triggered()),glWidget,SLOT(setCaptureInterval()));

  refreshTimer = new QTimer(this);
  refreshTimer->start(150);
  ValueItem::refreshTimer = refreshTimer;
  simulationTimer = new QTimer(this);
  simulationTimer->start(1);
  connect(simulationTimer,SIGNAL(timeout()),this,SLOT(simulationCallback()));
  
  // show the window
  mainWindow->show();
  loadWindowState();
  
  glWidget->setFramerate(60);

  glWidget->startRendering();

  updateActions();
  return true;
}
void QtSimulationRunner::setFramerate(double rate){
  glWidget->setFramerate(rate);
}
void QtSimulationRunner::step(){
  _realTimeModule->setPause(true);
 // _realTimeModule->advanceBy(0.1);
}
void QtSimulationRunner::togglePause(){
  _realTimeModule->togglePause();
}
bool QtSimulationRunner::isPausing(){
  return _realTimeModule->isPaused();
}
void QtSimulationRunner::onPotentialSimulationObjectAdd(ISimulationObject * obj){
  SimulationRunner::onPotentialSimulationObjectAdd(obj);
  auto rtsModule = dynamic_cast<SimulationTimeController*>(obj);
  if(rtsModule){
    _realTimeModule = rtsModule;
    _timeControl->setRealTimeModule(rtsModule);
  }
  auto action = dynamic_cast<IAction*>(obj);
  if(action){
    addAction(action);
  }
  auto component = dynamic_cast<IComponent*>(obj);
  if(component){
   
    ValueItemFactory::create(*_rootNode,component);
    if(propertyUi){
      propertyUi->treeView->expandAll();
      propertyUi->treeView->resizeColumnToContents(0);
      propertyUi->treeView->resizeColumnToContents(1);
      propertyUi->treeView->resizeColumnToContents(2);
      propertyUi->treeView->resizeColumnToContents(4);
      propertyUi->treeView->resizeColumnToContents(5);

    }//_rootNode->appendRow(item);
  }

}
void QtSimulationRunner::updateActions(){
  if(!isInitialized())return;
  ui->menuInteraction->clear();

  for_each(_actions.begin(), _actions.end(),[this](IAction* action){
    QAction * qaction = new QtSimulationAction(*action);
    ui->menuInteraction->addAction(qaction);    
  });
}

void QtSimulationRunner::addAction(IAction * action){
  _actions.push_back(action);
  
  updateActions();

}
void QtSimulationRunner::setPause(bool flag){
  _realTimeModule->setPause(flag);
}

int QtSimulationRunner::executeRunner(){
  return application->exec();
}

void QtSimulationRunner::simulationCallback(){	
  executeTasks();
}
