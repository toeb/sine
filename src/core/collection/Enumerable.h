#pragma once
#include <config.h>

#include <core.collection.h>
#include <core/collection/operations/OperationCollectionItemType.h>
#include <core/collection/operations/OperationCollectionItemAccess.h>
namespace nspace{
  namespace collection{

    

    template<typename Container>
    class Enumerable{
    private:
      Container _container;
      typedef CollectionItemType<Container>::ItemType type;
      typedef CollectionItemType<Container>::IndexType index;
    public:
      inline auto operator[](const index & i)->type{
        return item(_container);
      }

        
    };
  }
}