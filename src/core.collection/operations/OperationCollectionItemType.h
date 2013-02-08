#pragma once

#include <core.operation.h>

// creates a specialization for CollectionItemType
#define SpecializeCollectionItemType(COLLECTIONTYPE)\
  template<typename T>\
class CollectionItemType<COLLECTIONTYPE>{\
public:\
  typedef T ItemType;\
};

namespace nspace{
  template<typename CollectionType>
  class CollectionItemType{
  public:
    typedef void ItemType;
  };
}
