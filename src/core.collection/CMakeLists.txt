set(source ../include/core.collection.h )


set(collectionOperationsSource
  ./operations/OperationCollectionSetItem.h
  ./operations/OperationCollectionItemType.h
  ./operations/OperationCollectionGetItem.h  
  ./operations/OperationCollectionItemAccess.h
  ./operations/OperationCollectionItemAccessMutable.h
  ./operations/OperationCollectionSize.h
  ./operations/OperationCollectionAddElement.h
  ./operations/OperationCollectionRemoveElement.h
  ./operations/OperationCollectionSwapElement.h
  ./operations/OperationCollectionForeach.h
  ./operations/OperationCollectionCopyRange.h
  ./operations/OperationEnumerableGetEnumerator.h
  ./operations/OperationEnumerableGetEnumerable.h


)
source_group("operations" FILES ${collectionOperationsSource})
set(source ${source} ${collectionOperationsSource})
set(collectionContainersSource
 ./containers/LinkedList.h
 ./containers/Array.h
 ./containers/Set.h
	
)
source_group("containers" FILES ${collectionContainersSource})
set(source ${source} ${collectionContainersSource})

set(linkedListSpecializationSource
  ./specialization/linkedlist/Enumerator.h
  ./specialization/linkedlist/AddItem.h
  ./specialization/linkedlist/RemoveItem.h

)
set(source ${source} ${linkedListSpecializationSource})
source_group("specialization\\linkedlist" FILES ${linkedListSpecializationSource})
set(managedarraySpecializationSource


)
set(source ${source} ${managedarraySpecializationSource})
source_group("specialization\\managedarray" FILES ${managedarraySpecializationSource})


set(setSpecializationSource

  ./specialization/dslib.h

)
set(source ${source} ${setSpecializationSource})
source_group("specialization\\set" FILES ${setSpecializationSource})


set(arraySpecializationSource

  ./specialization/array.h

)
set(source ${source} ${arraySpecializationSource})
source_group("specialization\\array" FILES ${arraySpecializationSource})


set(stdSpecializationSource
  ./specialization/std/Enumerator.h
  ./specialization/std/AddItem.h
  ./specialization/stdcontainer.h
)
set(source ${source} ${stdSpecializationSource})
source_group("specialization\\std" FILES ${stdSpecializationSource})


set(collectionSource
  ./Operators.h
  ./Operations.h
  ./Enumerable.h
  ./ObservableCollection.h
  ../include/core.collection.h
)


set(collectionMiscSource
 ./Query.h
 ./ValueLookup.h
 ./ValueLookup.cpp
 ./PairMap.h
 ./PairMap.cpp
 ./ObservableCollection.h

)

source_group("" FILES ${collectionSource})
set(source ${source} ${collectionSource})

add_library(core.collection  ${source} CMakeLists.txt)


set_target_properties(core.collection PROPERTIES LINKER_LANGUAGE CXX)