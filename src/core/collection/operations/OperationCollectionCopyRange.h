#pragma once

#include <core.operation.h>
#include <core/collection/Operations.h>

namespace nspace{




  //will copy anything.  this will cause errors if th target type is a pointer for example because it will write without knowing the targets size
  template<typename DestinationCollectionType, typename SourceCollectionType, typename IndexType>
  OPERATION(CollectionCopyRange){
    OPERATION_IMPLEMENTATION(bool &result,
      DestinationCollectionType & target,
      const SourceCollectionType & source,
      const IndexType & startSource, 
      const IndexType & endSource,
      const IndexType & startTarget){
        IndexType j=startTarget;
        IndexType i =startSource;
        CollectionItemType<DestinationCollectionType>::ItemType it ;
        while(i < endSource){
          item(it,source,i);
          setItem(target,it,j);
          i++;
          j++;
        }  
        result = true;
        return true;
    }
  };



}