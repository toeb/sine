#pragma once

#include <core.operation.h>

#define CollectionSetItemSpecialization(COLLECTIONTYPE,ITEMTYPE,INDEXTYPE,SETITEMCODE) \
  OPERATION_SPECIALIZATION{\
  SPECIALIZATION(COLLECTIONTYPE & collection ,const ITEMTYPE & item, const INDEXTYPE& index){SETITEMCODE; return true;}\
  }

namespace nspace{
  template<typename ItemType, typename CollectionType, typename IndexType>
  BINARY_OPERATION(CollectionSetItem, CollectionType & collection ,const ItemType & item, const IndexType& index,{return false;});
}