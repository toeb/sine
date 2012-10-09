#pragma once

#include <core.hub/CompositeHubObject.h>

namespace nspace{
  class SampleApplication;

  // the sample class needs to be derived and implemented 
  // the client needs to override setup in which he can add 
  // to the Samples components() set.
  // e.g.  
/*
  class MySample{
    protected:
    void setup(){
      Sphere * sphere = new Sphere(0.5);
      SphereRenderer * sphereRenderer = new SphereRenderer();
      sphereRenderer->add(sphere);

      components()|=sphere;
      components()|=sphereRenderer;

    }
  };
*/
  class Sample : public virtual CompositeHubObject{
    TYPED_OBJECT(Sample);
  protected:    
    virtual void setup()=0;  
    Sample();
    void setApplication(SampleApplication & application);
    SampleApplication & application();
  protected:
    friend class SampleApplication;
  private:
    SampleApplication * _application;
  };
}