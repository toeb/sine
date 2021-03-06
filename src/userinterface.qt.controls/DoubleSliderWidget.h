#include <QSlider>

#include <core.reflection.h>
#include <core/reflection/ITypedModifiableValue.h>
#include <core/PropertyChangingObject.h>

namespace nspace{
  class DoubleSliderWidget : public QSlider, public virtual ITypedModifiableValue<double>, public virtual PropertyChangingObject{
    Q_OBJECT;
    TYPED_OBJECT(DoubleSliderWidget);
    PROPERTY(double, MinValue){}
    PROPERTY(double, MaxValue){}
    PROPERTY(int, Steps){
      setRange(0,newvalue);
    }

  public:
    DoubleSliderWidget();
    protected slots:
      void valueChanged(int i);
  protected:

    bool storeTypedValue(const double  & value);
    bool retrieveTypeValue(double & value)const;
  };
}