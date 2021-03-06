set(source ../include/core.h )


set(preprocessorSource 
../include/core.preprocessor.h
./preprocessor/Basic.h
./preprocessor/Variadic.h
./preprocessor/Foreach.h
./preprocessor/Reduce.h

)
source_group("preprocessor" FILES ${preprocessorSource})
set(source ${source} ${preprocessorSource})

set(unifiedPropertyDefinitionSource
../include/core.properties.h
./properties/Extensible.h
./properties/Templated.h
./properties/Simple.h
./properties/Properties.h

)
source_group("properties" FILES ${unifiedPropertyDefinitionSource})
set(source ${source} ${unifiedPropertyDefinitionSource})



set(commandlineParserSource
  ./commandline/CommandLineParser.h
  ./commandline/CommandLineParser.cpp
  ./commandline/CommandLineArgumentDefinition.h
  ./commandline/CommandLineArgumentDefinition.cpp
  ./commandline/CommandLineArgument.h
  ./commandline/CommandLineArgument.cpp
  ../include/core.commandline.h
)
source_group("commandline" FILES ${commandlineParserSource})

set(source ${source} ${commandlineParserSource})

set(templateSource
./template/TemplateUtilities.h
./template/default_constructor.h
./template/is_singleton.h
./template/is_same_type.h
./template/result_of_static_function.h
./template/to_string.h

)

set(source ${source} ${templateSource})
source_group("template" FILES ${templateSource})

set(bindingSource
 ./binding/Binding.h
 ./binding/Binding.cpp
 ./binding/ValueConverter.h
 ./binding/ValueConverter.cpp
)
set(source ${source} ${bindingSource})
source_group("binding" FILES ${bindingSource})

set(operationSource
./operation/Operation.h
../include/core.operation.h
)
set(source ${source} ${operationSource})

source_group("operation" FILES ${operationSource})

set(collectionOperationsSource
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
  ./collection/operations/OperationEnumerableGetEnumerator.h
  ./collection/operations/OperationEnumerableGetEnumerable.h


)
source_group("collection\\operations" FILES ${collectionOperationsSource})
set(source ${source} ${collectionOperationsSource})
set(collectionContainersSource
 ./collection/containers/LinkedList.h
 ./collection/containers/Array.h
 ./collection/containers/Set.h
	
)
source_group("collection\\containers" FILES ${collectionContainersSource})
set(source ${source} ${collectionContainersSource})

set(linkedListSpecializationSource
  ./collection/specialization/linkedlist/Enumerator.h
  ./collection/specialization/linkedlist/AddItem.h
  ./collection/specialization/linkedlist/RemoveItem.h

)
set(source ${source} ${linkedListSpecializationSource})
source_group("collection\\specialization\\linkedlist" FILES ${linkedListSpecializationSource})
set(managedarraySpecializationSource


)
set(source ${source} ${managedarraySpecializationSource})
source_group("collection\\specialization\\managedarray" FILES ${managedarraySpecializationSource})


set(setSpecializationSource

  ./collection/specialization/dslib.h

)
set(source ${source} ${setSpecializationSource})
source_group("collection\\specialization\\set" FILES ${setSpecializationSource})


set(arraySpecializationSource

  ./collection/specialization/array.h

)
set(source ${source} ${arraySpecializationSource})
source_group("collection\\specialization\\array" FILES ${arraySpecializationSource})


set(stdSpecializationSource
  ./collection/specialization/std/Enumerator.h
  ./collection/specialization/std/AddItem.h
  ./collection/specialization/stdcontainer.h
)
set(source ${source} ${stdSpecializationSource})
source_group("collection\\specialization\\std" FILES ${stdSpecializationSource})


set(collectionSource
  ./collection/Operators.h
  ./collection/Operations.h
  ./collection/Enumerable.h
  ../include/core.collection.h
)

source_group("collection" FILES ${collectionSource})
set(source ${source} ${collectionSource})

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
./reflection/DefaultTypes.h
./reflection/DefaultTypes.cpp
./reflection/TypeInfo.h
./reflection/TypeInfo.cpp
./reflection/TypeRepository.h
./reflection/TypeRepository.cpp


./reflection/Converter.h
./reflection/Converter.cpp
../include/core.reflection.h
)
source_group("reflection" FILES ${reflectionSource})
set(source ${source} ${reflectionSource})


set(utilitySource
./utilities/StringTools.h
./utilities/StringTools.cpp
./utilities/SourceInfo.h
./utilities/SourceInfo.cpp
./utilities/Helpers.h
./utilities/Helpers.cpp
./utilities/Utilities.h
./utilities/Utilities.cpp
./utilities/Timer.h
./utilities/Timer.cpp
./utilities/ToString.h
./utilities/ToString.cpp
../include/core.utilities.h

)

source_group("utilities" FILES ${utilitySource})
set(source ${source} ${utilitySource})

set(graphSource

./graph/TypedNode.h
./graph/DataNode.h
./graph/DerivableDataNode.h
./graph/Node.h
./graph/Node.cpp
./graph/Graph.h
./graph/Graph.cpp
../include/core.graph.h
)

source_group("graph" FILES ${graphSource})
set(source ${source} ${graphSource} )

set(rootSource
./Time.h
./Time.cpp
./Members.h

./Object.h
./Object.cpp
./NamedObject.h
./NamedObject.cpp


./Observable.h
./Observable.cpp
./PropertyChangingObject.h
./PropertyChangingObject.cpp

./ObservableCollection.h

./Comparator.h
./Query.h
./ValueLookup.h
./ValueLookup.cpp
./PairMap.h
./PairMap.cpp
./Serialization.h
../config.h
../include/core.h
)
source_group("" FILES ${rootSource} )
set(source ${source} ${rootSource})
set(patternsSource
./patterns/Derivable.h
./patterns/ValueHolder.h
./patterns/Composite.h
./patterns/ArrayPool.h
./patterns/Visitor.h
./patterns/Singleton.h
./patterns/Decorator.h
./patterns/Multiton.h
./patterns/StaticInitializer.h
)
set(source ${source} ${patternsSource})
source_group("patterns" FILES ${patternsSource})
add_library(core  ${source} CMakeLists.txt)

