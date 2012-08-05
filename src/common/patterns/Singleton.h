#pragma once
#include <common/Config.h>
namespace nspace{
template<typename DerivedType>
class Singleton{
 protected:
  Singleton(){
    if(instanceData()){
      std::cerr << "Double instanciation of Singleton"<<std::endl;
    }
    *instanceData() = static_cast<DerivedType*>(this);
  }
private:
  static DerivedType ** instanceData(){
    static DerivedType ** _instanceData=0;
    return _instanceData;
  }
public:
  static DerivedType& instance(){
    if(!instanceData())new DerivedType();
    return **instanceData();
  }
};

}