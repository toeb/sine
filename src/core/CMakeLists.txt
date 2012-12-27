set(bindingSource
 ./binding/Binding.h
 ./binding/Binding.cpp
 ./binding/ValueConverter.h
 ./binding/ValueConverter.cpp
)

set(operationSource
./operation/Operation.h
../include/core.operation.h
)

source_group("operation" FILES ${operationSource})

set(collectionSource
  ./collection/operations/OperationCollectionSetItem.h
  ./collection/operations/OperationCollectionItemType.h
  ./collection/operations/OperationCollectionGetItem.h  
  ./collection/operations/OperationCollectionItemAccess.h
  ./collection/operations/OperationCollectionItemAccessMutable.h
  ./collection/operations/OperationCollectionSize.h
  ./collection/operations/OperationCollectionAddElement.h
  ./collection/operations/OperationCollectionRemoveElement.h
  ./collection/operations/OperationCollectionSwapElement.h
  ./collection/operations/OperationCollectionForeach.h
  ./collection/operations/OperationCollectionCopyRange.h
  ./collection/Operators.h
  ./collection/Operations.h
  ./collection/Enumerable.h
  ./collection/specialization/array.h
  ./collection/specialization/stdcontainer.h
  ./collection/specialization/dslib.h
  ../include/core.collection.h
)

source_group("collection" FILES ${collectionSource})

source_group("binding" FILES ${bindingSource})

set(reflectionSource
./reflection/MethodInfo.h
./reflection/MethodInfo.cpp
./reflection/Attribute.h
./reflection/Attribute.cpp
./reflection/PropertyInfo.h
./reflection/PropertyInfo.cpp
./reflection/PropertySetInfo.h
./reflection/PropertySetInfo.cpp
./reflection/TypedPropertySetInfo.h
./reflection/TypedPropertySetInfo.cpp
./reflection/TypedProperty.h
./reflection/TypedProperty.cpp
./reflection/MemberInfo.h
./reflection/MemberInfo.cpp
./reflection/PropertyAdapter.h
./reflection/PropertyAdapter.cpp
./reflection/MethodAdapter.h
./reflection/MethodAdapter.cpp
./reflection/Type.h
./reflection/Type.cpp
./reflection/Reflection.h
./reflection/Action.h
./reflection/Action.cpp
./reflection/DelegateAction.h
./reflection/DelegateAction.cpp
./reflection/DelegateValue.h
./reflection/DelegateValue.cpp
./reflection/IModifiableValue.h
./reflection/IModifiableValue.cpp
./reflection/IReadableValue.h
./reflection/IReadableValue.cpp
./reflection/ISerializable.h
./reflection/ISerializable.cpp
./reflection/ITypedModifiableValue.h
./reflection/ITypedModifiableValue.cpp
./reflection/ITypedReadableValue.h
./reflection/ITypedReadableValue.cpp
./reflection/MethodAction.h
./reflection/MethodAction.cpp
./reflection/ReferenceValue.h
./reflection/ReferenceValue.cpp
./reflection/ITypedSerializableValue.h
./reflection/ITypedSerializableValue.cpp
./reflection/MemberAdapter.h
./reflection/MemberAdapter.cpp

./reflection/Converter.h
./reflection/Converter.cpp
../include/core.reflection.h
)
source_group("reflection" FILES ${reflectionSource})

set(source
./Time.h
./Time.cpp
./Object.h
./Object.cpp
./Members.h
./NamedObject.h
./NamedObject.cpp
./TypedNode.h
./DataNode.h
./DerivableDataNode.h
./Node.h
./Node.cpp
./Graph.h
./Graph.cpp
./Comparator.h
./ObservableCollection.h
./Query.h
./Set.h
./StringTools.h
./StringTools.cpp
./ValueLookup.h
./ValueLookup.cpp
./PairMap.h
./PairMap.cpp
./PropertyChangingObject.h
./PropertyChangingObject.cpp
./Observable.h
./Observable.cpp
./Serialization.h
../config.h
../include/core.h
)
source_group("" FILES ${source} )
set(patternsSource
./patterns/Derivable.h
./patterns/ValueHolder.h
./patterns/Composite.h
./patterns/ArrayPool.h
./patterns/Visitor.h
./patterns/Singleton.h
./patterns/Decorator.h
)
source_group("src\\patterns" FILES ${patternsSource})
add_library(core ${source} ${patternsSource} ${reflectionSource} ${bindingSource} ${collectionSource} ${operationSource} CMakeLists.txt)

