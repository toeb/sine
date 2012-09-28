#pragma once
#include <core/Object.h>
namespace nspace{
class Initializable : public virtual Object{
TYPED_OBJECT;
private:
  bool _initialized;
public:
  Initializable():_initialized(false){}
  const inline bool isInitialized()const{return _initialized;}
  bool initialize();
  bool cleanup();
protected:
  virtual void cleanupObject(){};
  virtual bool initializeObject(){return true;}
  virtual void onObjectInitialized(){};
};

}