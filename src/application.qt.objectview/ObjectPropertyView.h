#pragma once

#include <core.h>
#include <QWidget>
#include <application.qt.objectview/ObjectPropertyViewModel.h>
class Ui_ObjectPropertyView;
namespace nspace{

  class ObjectPropertyView : 
    public QWidget, 
    public virtual PropertyChangingObject,
    public virtual Log
  {
    Q_OBJECT;
    REFLECTABLE_OBJECT(ObjectPropertyView);
    Ui_ObjectPropertyView * _ui;
    ObjectPropertyViewModel * _model;
  public:
    ObjectPropertyView(QWidget*parent=0);

    PROPERTY(Object*, CurrentObject);
    PROPERTYSET(QWidget* , Widgets,,);

    public slots:
      void onModelLayoutChanged(const QModelIndex & index);
      void autoresize();
  };

}