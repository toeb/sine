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
 * \file src/vis/qt_model_viewer/QtModelViewer.h
 * 
 */
#pragma once
#include <simulation.runner/SimulationRunner.h>
#include <simulation.runner.qt/QtTimeControl.h>
#include <simulation.runner.qt/QtSnapshotControl.h>

#include <QApplication>
#include <QMainWindow>
#include <QElapsedTimer>
#include <QGLWidget>
#include <QSettings>

#include <simulation.runner.qt/GlWidget.h>
#include <simulation.time/SimulationTimeController.h>
#include <vector>

#include <QStandardItemModel>
#include <QStandardItem>

#include <simulation.access/IAction.h>

class Ui_MainWindow;
class Ui_PropertyWindow;


namespace nspace{

/**
 * \brief The Model Viewer. 
 *
 * \author Tobias Becker
 * \date 05.04.2012
 */
class QtSimulationRunner : public QObject, public virtual SimulationRunner{
  Q_OBJECT
private:
  SimulationTimeController * _realTimeModule;
  std::vector<IAction*> _actions;
public:

  /**
   * \brief Constructor.
   * 				
   * 				expects a valid renderer and the command line arguements 
   * 				starts in paused mode per default
   * 				
   * 				allows single steps in the simulation
   * 				
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param [in,out] renderer The renderer.
   * \param argc              (optional) the argument count.
   * \param argv              (optional) [in,out] If non-null, the arguement vector.
   * \param startPaused       (optional) start paused.
   */
  QtSimulationRunner( int argc=0, char** argv=0, bool startPaused=true);


  /**
   * \brief Destructor.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  ~QtSimulationRunner();

  void addAction(IAction * action);

  void updateActions();


  /**
   * \brief Query if the simulation is pausing.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \return true if pausing, false if not.
   */
  bool isPausing();

public slots:  

  /**
   * \brief Steps this object. by one timestep
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void step();

  /**
   * \brief Saves the window's state.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void saveWindowState();

  /**
   * \brief Loads the window's state.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void loadWindowState();

  /**
   * \brief Sets opengl to wireframe mode.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param on true to on.
   */
  void wireframe(bool on);

  /**
   * \brief Toggles simulation pause.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void togglePause();

  /**
   * \brief Sets simulation pause.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param on true to on.
   */
  void setPause(bool on);

  /**
   * \brief Sets the framerate of the underlying glwidget(s).
   *
   * \author Tobias Becker
   * \date 05.04.2012
   *
   * \param rate The rate.
   */
  void setFramerate(double rate);
protected slots:
	void onSimulationSet();
  /**
   * \brief Callback, gets called when the simulation timer times out.
   *
   * \author Tobias Becker
   * \date 05.04.2012
   */
  void simulationCallback();
protected:            
  //SimulationRunner overrides                           
  int executeRunner();
  bool initializeRunner();

  // simulationbase module override
  void onPotentialSimulationObjectAdd(ISimulationObject * obj);
private:
  QtTimeControl * _timeControl;
  ///< The user interface of the main window
  Ui_MainWindow * ui;
  Ui_PropertyWindow * propertyUi;
  QtSnapshotControl * _snapshotControl;

  ///< pointer to the main window
  QMainWindow * mainWindow;
  ///< pointer to the property window
  QDockWidget * propertyWindow;  
  ///< The gl widget
  GlWidget * glWidget;
  ///< The simulation timer
  QTimer * simulationTimer;     
  QTimer * refreshTimer;
  ///< stores settings in user folder
  QSettings settings;
  ///< The application
  QApplication * application; 
  ///< The arg count
  int & argc; 
  ///< The arg vector
  char** argv;
  QStandardItem * _rootNode;
  QStandardItemModel * _itemModel;

};//class QtModelViewer
}//namespace mbslib
