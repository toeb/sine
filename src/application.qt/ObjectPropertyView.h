#pragma once

#include <core/Object.h>
#include <core/Reflection.h>
#include <QWidget>
#include <application.qt/ObjectPropertyViewModel.h>
class Ui_ObjectPropertyView;
namespace nspace{

  class ObjectPropertyView : public QWidget, public virtual PropertyChangingObject{
    Q_OBJECT;
    REFLECTABLE_OBJECT(ObjectPropertyView);
    Ui_ObjectPropertyView * _ui;
    ObjectPropertyViewModel * _model;
  public:
    ObjectPropertyView(QWidget*parent=0);

    PROPERTY(Object*, CurrentObject);
    PROPERTYSET(QWidget* , Widgets,,);
  };

}