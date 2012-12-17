#pragma once
#include <core/collection/operations/OperationCollectionItemType.h>
#include <core/collection/operations/OperationCollectionSize.h>
#include <core/collection/operations/OperationCollectionItemAccess.h>
namespace nspace{

  SpecializeCollectionItemType(T*);
  template<typename T,size_t n>
  class CollectionItemType<T[n]>{
  public:
    typedef T ItemType;
  };
  // specialization for fixed size arrays -- need to be written out beca
  template<typename T, size_t n> OPERATION_SPECIALIZATION(CollectionSize)<T[n],size_t>{
    SPECIALIZATION(size_t & thesize, const T* arr){
      thesize=n;
      return true;
    }
  };

  template<typename T, typename IndexType, size_t n> OPERATION_SPECIALIZATION(CollectionSetItem)<T,T[n],IndexType>{
    SPECIALIZATION(T* arr, const T & it, const IndexType & index){
      arr[index]=it;
      return true;
    }
  };

template<typename T, typename IndexType> OPERATION_SPECIALIZATION(CollectionSetItem)<T,T*,IndexType>{
    SPECIALIZATION(T* arr, const T & it, const IndexType & index){
      arr[index]=it;
      return true;
    }
  };





  template<typename T,  typename IndexType, size_t n> OPERATION_SPECIALIZATION(CollectionItemAccess)<T,T[n],IndexType>{
    SPECIALIZATION(T & it, T* arr, const IndexType & index){
      it = arr[index];
      return true;
    }
  };
  template<typename T,  typename IndexType, size_t n> OPERATION_SPECIALIZATION(CollectionPointerAccess)<T,T[n],IndexType>{
    SPECIALIZATION(T ** it, T* arr, const IndexType & index){
      *it = &arr[index];
      return true;
    }
  };
  template<typename T,  typename IndexType> OPERATION_SPECIALIZATION(CollectionPointerAccess)<T,T*,IndexType>{
    SPECIALIZATION(T ** it, T* arr, const IndexType & index){
      *it = &arr[index];
      return true;
    }
  };




  template<typename T, typename IndexType> CollectionItemAccessSpecialization(T, T *, IndexType,item = collection[index])
    //template<typename T, typename IndexType> CollectionItemAccessSpecialization(T , T *, IndexType,*item = &collection[index])
    //template<typename T> CollectionItemAccessMutableSpecialization(T , T*, size_t,*item = &collection[index])

}