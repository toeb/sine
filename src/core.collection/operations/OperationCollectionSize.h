#pragma once

#include <core/operation/Operation.h>

// macro for easy specialization of operationcollectionsize
// needs to be called inside namespace nspace{}
// ASSIGNSIZECODE needs to set SizeType & size variable
#define OperationCollectionSizeSpecialization(COLLECTIONTYPE,SIZETYPE, ASSIGNSIZECODE) \
  OPERATION_SPECIALIZATION(CollectionSize)<COLLECTIONTYPE,SIZETYPE> {\
  SPECIALIZATION (SIZETYPE & size, const COLLECTIONTYPE & collection){{ASSIGNSIZECODE}return true;}\
  };

/*
class OperationCollectionSize<COLLECTIONTYPE, SIZETYPE>{\
public:\
static inline bool operation(SIZETYPE & size, const COLLECTIONTYPE & collection){{ASSIGNSIZECODE}return true;}\
};\
*/
namespace nspace{
  template<typename CollectionType, typename SizeType> UNARY_OPERATION(CollectionSize, SizeType & size, const CollectionType & collection, size=0;return false;)
}