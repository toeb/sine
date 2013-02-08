#pragma once

#include <core/collection/operations/OperationCollectionSize.h>
#include <core/collection/operations/OperationCollectionItemType.h>
#include <core/collection/containers/Set.h>
namespace nspace{
  SpecializeCollectionItemType(Set<T>);

  template<typename T, typename IndexType> OperationCollectionSizeSpecialization(Set<T>,IndexType, size=collection.size(););
  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T,Set<T>,IndexType,item=collection.at(index));
  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T,const Set<T>,IndexType,item=collection.at(index));

  //template<typename T, typename IndexType> CollectionSetItemSpecialization(Set<T>,T,IndexType,collection.set(index,item));
}