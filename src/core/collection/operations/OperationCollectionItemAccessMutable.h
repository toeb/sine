#pragma once
#include <core.operation.h>

// this macro helps specialize item access 
// implementation example: 
// CollectionItemAccessSpecialization(int, int*, int, *item = &collection[index])
#define CollectionItemAccessMutableSpecialization(ITEMTYPE,COLLECTIONTYPE,INDEXTYPE, ACCESSITEMCODE)\
  OPERATION_SPECIALIZATION(CollectionItemAccessMutable)<ITEMTYPE,COLLECTIONTYPE,INDEXTYPE>{\
  SPECIALIZATION(ITEMTYPE ** item, COLLECTIONTYPE & collection ,const INDEXTYPE& index){if(item==0)return false; {ACCESSITEMCODE;} return true;}\
  };

namespace nspace{
  template<typename ItemType, typename CollectionType, typename IndexType> 
  BINARY_OPERATION(CollectionItemAccessMutable,ItemType ** item,CollectionType & collection ,const IndexType& index,{item=0; return false;});


}
