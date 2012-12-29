#include "ActionWidget.h"
#include <QBoxLayout>
using namespace nspace;
using namespace std;

ActionWidget::ActionWidget(QWidget * parent):DynamicWidget(parent){
  _button = new QPushButton;
  _button->setText("Execute");
  auto layout = new QHBoxLayout(this);

  _button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  setFocusProxy(_button);
  layout->addWidget(_button);
  layout->setSpacing(0);
  layout->setMargin(0);

  connect(_button,SIGNAL(clicked()),this,SLOT(performAction()));
  setAutoFillBackground(true);
}
void ActionWidget::onDataContextChanging(Object * oldvalue, Object * newvalue){
  auto value = dynamic_cast<Action*>(newvalue);
  setAction(value);
}
void ActionWidget::performAction(){
  if(getAction()){
    getAction()->execute();
  }
}