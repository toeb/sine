#include <QSlider>

#include <core.reflection.h>

#include <core/PropertyChangingObject.h>

namespace nspace{
  class DoubleSliderWidget : public QSlider, public virtual IModifiableValue, public virtual PropertyChangingObject{
    Q_OBJECT;
    reflect_type(DoubleSliderWidget);
    typedef double reflect_property(MinValue);
    typedef double reflect_property(MaxValue);
    typedef int reflect_property(Steps);

    auto after_set(Steps){
      setRange(0,getSteps());    
    }


  public:
    DoubleSliderWidget();
    protected slots:
      void valueChanged(int i);
  protected:

    bool storeValue(Argument argument) override ;
    Argument retrieveValue()const override ;
  };
}