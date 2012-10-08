#pragma once

#include <core.hub/CompositeHubObject.h>

namespace nspace{
  class SampleApplication;

class Sample : public virtual CompositeHubObject{
  TYPED_OBJECT(Sample);
  SampleApplication * _application;
protected:
  friend class SampleApplication;
  Sample():_application(0){}
  void setApplication(SampleApplication & application){_application = &application;}
  SampleApplication & application(){return *_application;}
public:    
  virtual void setup()=0;
};
}