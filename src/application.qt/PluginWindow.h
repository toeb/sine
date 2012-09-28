#pragma once

#include <QDockWidget>
#include <config.h>
namespace nspace{
  class PluginWindow : public QDockWidget{
    Q_OBJECT;
signals:
    // window closed signal is emitted when this window is closed
    void windowClosed();
  protected:
    // overrides closeevent to catch emit the window closed signal
    void closeEvent(QCloseEvent * e);
  public:
    // constructor
    PluginWindow(QWidget * parent=0);
  };
}