#pragma once
#include <config.h>
#include <core.collection/operations/OperationCollectionItemType.h>
namespace nspace{


template <typename EnumerableType>
class EnumerableItemType{
public:
    typedef typename CollectionItemType<EnumerableType>::ItemType ItemType;
};
template<typename IndexableType>
class IndexableIndexType{
public:
    typedef size_t IndexType;
};
namespace collection{
// returns true if size of collection could be determined.  then n is set to the number if items in colleciton
template<typename SizeType,typename CollectionType>
bool size(SizeType & n, const CollectionType & collection);
// returns the size of the collection.  if the size cannot be determined the result is undefined
template<typename SizeType,typename CollectionType>
SizeType size(const CollectionType & collection);
// returns the size of the collection (size_t)
template<typename CollectionType> auto size(const CollectionType & collection)->typename IndexableIndexType<CollectionType>::IndexType;
// returns true if the item at index could be accessed. then the item is assigned th ith item
template<typename ItemType, typename CollectionType, typename IndexType>
inline bool item(ItemType & item, CollectionType & collection, const IndexType & i);
// returns th ith item of the collection
template<typename ItemType, typename CollectionType, typename IndexType>
inline ItemType item(CollectionType & collection, const IndexType & i);
// returns true if the collection supports returning pointers to the item. if it does ptr is assign the pointer to the ith item in the collection
template<typename ItemType, typename CollectionType, typename IndexType>
inline bool pointer(ItemType ** ptr, CollectionType & collection, const IndexType & i);
// return the pointer to the ith item in the collection (returns null if the colleciton is not capable of returning pointers)
template<typename CollectionType, typename IndexType>
inline auto pointer(CollectionType & collection, const IndexType & index)->typename CollectionItemType<CollectionType>::ItemType*;
// returns a reference to the ith item.  this method will cause a failure if the item is invalid or the collection does not support returning pointers
template<typename ItemType, typename CollectionType, typename IndexType>
inline ItemType & reference(CollectionType & collection, const IndexType & i);
// returns true if item i of the collection could be successfully set
template<typename ItemType, typename CollectionType, typename IndexType>
inline bool setItem(CollectionType & collection, const ItemType & item, const IndexType & i);
// copies elements from source[i...j-1] to target[k...k+(j-i)-1]
template<typename CollectionTypeA, typename CollectionTypeB, typename IndexType>
inline bool copyRange(CollectionTypeA & target, const CollectionTypeB & source, const IndexType & i, const IndexType & j, const IndexType & k);
// copies elements from source[0,n-1] to target[0,n-1]  you need to ensure that target has at least n slots
template<typename CollectionTypeA, typename CollectionTypeB>
inline bool copy(CollectionTypeA & target, const CollectionTypeB & source);
//returns the collections underyling array structure (if the collection has one) else nullptr is returned,
template<typename CollectionType>
inline typename CollectionItemType<CollectionType>::ItemType* underlyingArray(CollectionType & collection){
    return nullptr;
};
}
}


#include <core.collection/operations/OperationCollectionSize.h>
#include <core.collection/operations/OperationCollectionItemAccess.h>
#include <core.collection/operations/OperationCollectionSetItem.h>
#include <core.collection/operations/OperationCollectionCopyRange.h>

namespace nspace{
namespace collection{
//IMPLEMENTATION

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

template<typename CollectionType> auto size(const CollectionType & collection)->typename IndexableIndexType<CollectionType>::IndexType{
    return size<typename IndexableIndexType<CollectionType>::IndexType,CollectionType>(collection);
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
template<typename CollectionType, typename IndexType>
inline auto pointer(CollectionType & collection, const IndexType & index)->typename CollectionItemType<CollectionType>::ItemType*{
    typename CollectionItemType<CollectionType>::ItemType* ptr;
    pointer(&ptr,collection,index);
    return ptr;
}

template<typename CollectionType, typename IndexType>
inline auto  reference(CollectionType & collection, const IndexType & index)->typename CollectionItemType<CollectionType>::ItemType&{
    return *pointer(collection,index);
}

template<typename ItemType, typename CollectionType, typename IndexType>
inline bool setItem(CollectionType & collection, const ItemType & item, const IndexType & index){
    return OperationCollectionSetItem<ItemType,CollectionType,IndexType>::operation(collection,item,index);
}

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
}
}
