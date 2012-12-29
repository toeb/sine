#include "GlWidgetPluginWindow.h"
#include <visualization.opengl.qt/GlWidget.h>
#include "ui_glviewportwidget.h"

using namespace nspace;

GlWidgetPluginWindow::GlWidgetPluginWindow(Set<GlViewport*> & viewports):PluginWindow(0),_viewports(viewports),_glWidget(0),_ui(0){
  setName("GlWidgetPluginWindow");
  viewports.addObserver(this);
  _ui = new Ui_GlViewportWidget();
  QWidget * widget = new QWidget();

  _ui->setupUi(widget);
  this->setWidget(widget);
  _glWidget= new GlWidget();
  auto layout = new QVBoxLayout(_ui->widget);
  layout->setMargin(0);

  layout->addWidget(_glWidget);

  viewports.foreachElement([this](GlViewport * viewport){
    elementAdded(&_viewports,viewport);
  });
  connect(_ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT( viewportIndexChanged(int)));

  Components()|=_glWidget;
}

void GlWidgetPluginWindow::viewportIndexChanged(int idx){
  auto variant =_ui->comboBox->itemData(idx);
  auto dataPtr = variant.value<void*>();
  auto viewport = static_cast<GlViewport*> (dataPtr);
  _glWidget->setViewport(viewport);
}

void GlWidgetPluginWindow::elementAdded(ObservableCollection<GlViewport*> * sender, GlViewport* element){
  _ui->comboBox->addItem(element->name().c_str(), qVariantFromValue<void*>(element));
}
void GlWidgetPluginWindow::elementRemoved(ObservableCollection<GlViewport*> * sender, GlViewport* element){
}