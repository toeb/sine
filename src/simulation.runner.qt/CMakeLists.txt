set(runnerSource
./QtSimulationRunner.h
./QtSimulationRunner.cpp	
./GlWidget.h
./GlWidget.cpp
./QtSimulationAction.h
./QtSimulationAction.cpp
./ValueItem.h
./ValueItem.cpp
./IValueItem.h
./IValueItem.cpp
./NamedItem.h
./NamedItem.cpp
./ValueItemDelegate.h
./ValueItemDelegate.cpp
./IValueItem.h
./ValueItemFactory.h
./ValueItemFactory.cpp
./DoubleItem.h
./DoubleItem.cpp
./QtTimeControl.h
./QtTimeControl.cpp
./QtSnapshotControl.h
./QtSnapshotControl.cpp 
./QtPropertyView.h
./QtPropertyView.cpp
./QtSimulationObjectsView.h
./QtSimulationObjectsView.cpp
./SimulationDockWidget.h
./SimulationDockWidget.cpp
./QtTaskRunner.h
./QtTaskRunner.cpp
./QtViewport.h
./QtViewport.cpp
./QtTimeControlPlugin.h
./QtTimeControlPlugin.cpp
./QtSnapshotPlugin.h
./QtSnapshotPlugin.cpp
./QtLogViewPlugin.h
./QtLogViewPlugin.cpp
)

set(runnerMocFiles
#./QtSnapshotPlugin.h
#./QtTimeControlPlugin.h
./QtSimulationObjectsView.h
./QtTimeControl.h
#./QtSimulationRunner.h
#./GlWidget.h
./QtSimulationAction.h
./ValueItem.h
./ValueItemDelegate.h
./QtSnapshotControl.h
./QtPropertyView.h
./SimulationDockWidget.h
./QtTaskRunner.h
#./QtViewport.h
#./QtLogViewPlugin.h
)

set(runnerUiFiles
simulationobjects.ui
mainwindow.ui
timecontrol.ui
propertyView.ui
logView.ui
objectView.ui
statehistory.ui
taskwidget.ui
)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
#include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
add_definitions(-DQT)
include(${QT_USE_FILE})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
QT4_WRAP_CPP(runnerMoc ${runnerMocFiles})
QT4_WRAP_UI(runnerUi ${runnerUiFiles})

source_group("src" FILES ${runnerSource})
source_group("src\\autogenerated" FILES ${runnerMoc} ${runnerUi})
source_group("src\\ui" FILES ${runnerUiFiles})

add_library(simulation.runner.qt ${runnerSource} ${runnerMoc} ${runnerUi})
target_link_libraries(simulation.runner.qt
   application.qt
   simulation
   simulation.runner 
   simulation.time 
   core.task
   visualization.opengl 
   simulation.interaction 
   simulation.integration 
   simulation.history 
   simulation.access 
   userinterface.qt.controls
   ${QT_LIBRARIES})
	   