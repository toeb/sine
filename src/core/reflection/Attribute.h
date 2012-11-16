#pragma once


#include <core/reflection/Type.h>
#include <core/Object.h>
#include <math/Interval.h>
namespace nspace{
  
  class Attribute{
    TYPED_OBJECT(Attribute);
  };

  class DisplayAttribute :public virtual Attribute{
    TYPED_OBJECT(DisplayAttribute);
    SUBCLASSOF(Attribute);
    SIMPLE_PROPERTY(std::string, DisplayName);
    SIMPLE_PROPERTY(std::string, GroupName);
    SIMPLE_PROPERTY(uint, Order);
  };

  class DecimalAttribute : public virtual Attribute{
    TYPED_OBJECT(DecimalAttribute);
    SUBCLASSOF(Attribute);

    SIMPLE_PROPERTY(Interval,Range){}
    SIMPLE_PROPERTY(double, StepSize){}
    
  };

  class NavigatableAttribute:
    public virtual Attribute{
    TYPED_OBJECT(NavigatableAttribute);
    
  };

}