#pragma once

#include <core/collection/operations/OperationCollectionItemType.h>
#include <core/collection/operations/OperationCollectionSize.h>
#include <core/collection/operations/OperationCollectionItemAccess.h>
#include <core/collection/operations/OperationCollectionSetItem.h>

namespace nspace{

  namespace collection{
    template<typename SizeType,typename CollectionType>
    bool size(SizeType & n, const CollectionType & collection){  
      return OperationCollectionSize<CollectionType,SizeType>::operation(n,collection);
    }
    template<typename SizeType,typename CollectionType> SizeType size(const CollectionType & collection){
      SizeType n;
      if(!size(n,collection)){
        n=0; return n;
      }
      return n;
    }
    template<typename CollectionType> size_t size(const CollectionType & collection){
      size_t n;
      if(!size(n,collection)){
        n=0; return n;
      }
      return n;
    }


    
    template<typename ItemType, typename CollectionType, typename IndexType>
    inline bool item(ItemType & item, CollectionType & collection, const IndexType & index){      
      return OperationCollectionItemAccess<ItemType,CollectionType,IndexType>::operation(item,collection,index);
    }
    template<typename ItemType, typename CollectionType, typename IndexType>
    inline ItemType item(CollectionType & collection, const IndexType & index){
      ItemType it;
      item(it,collection,index);
      return it;
    }

        
    template<typename ItemType, typename CollectionType, typename IndexType>
    inline bool pointer(ItemType ** ptr, CollectionType & collection, const IndexType & index){
      return OperationCollectionPointerAccess<ItemType,CollectionType,IndexType>::operation(ptr,collection,index);
    }
    template<typename ItemType, typename CollectionType, typename IndexType>
    inline ItemType* pointer(CollectionType & collection, const IndexType & index){
      ItemType* ptr;
      pointer(&ptr,collection,index);
      return ptr;
    }


    template<typename ItemType, typename CollectionType, typename IndexType>
    inline ItemType & reference(CollectionType & collection, const IndexType & index){
      *pointer();

    }

    
    template<typename ItemType, typename CollectionType, typename IndexType>
    inline bool setItem(CollectionType & collection, const ItemType & item, const IndexType & index){
      return OperationCollectionSetItem<ItemType,CollectionType,IndexType>::operation(collection,item,index);
    }
  }
}


// copy range needs access to previous functions
#include <core/collection/operations/OperationCollectionCopyRange.h>

namespace nspace{
 namespace collection{   
   // copies elements from sourceStart to sourceEnd-1 to target from index targetStart
    template<typename CollectionTypeA, typename CollectionTypeB, typename IndexType>
    inline bool copyRange(CollectionTypeA & destination, const CollectionTypeB & source, const IndexType & sourceStart, const IndexType & sourceEnd, const IndexType & destinationStart){
      bool result=false;
      OperationCollectionCopyRange<CollectionTypeA,CollectionTypeB,IndexType>::operation(result,destination,source,sourceStart,sourceEnd,destinationStart);
      return result;      
    }

    template<typename CollectionTypeA, typename CollectionTypeB>
    inline bool copy(CollectionTypeA & destination, const CollectionTypeB & source){
      return copyRange<CollectionTypeA,CollectionTypeB,size_t>(destination,source,0,size(source),0);
    }



    
    
    /*template<typename ItemType, typename CollectionType, typename IndexType>
    inline ItemType & item(CollectionType & collection, const IndexType & index){
      ItemType ** ptr;
      OperationCollectionItemAccessMutable<ItemType,CollectionType,IndexType>::operation(ptr,collection,index);
      return **ptr;
    }*/



  }
}