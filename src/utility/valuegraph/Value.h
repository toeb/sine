#pragma once

#include <common/Config.h>

namespace nspace{ 
typedef long long VersionId;
class Value{
private:
  VersionId _version;
public:
  virtual const void * pointer()const=0;
  virtual void * pointer()=0;
  virtual void onValueChanged(){}  
  virtual void evaluate(){}

  Value():_version(0){}
  const long long & version()const{return _version;}
  
  inline void notifyChange(){
    _version++;
    onValueChanged();
  }  
};
}