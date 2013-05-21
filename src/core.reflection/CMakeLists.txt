set(source 
  ./ScopeInfo.h
  ./ScopeInfo.cpp
	./CMakeLists.txt
	../include/core.reflection.h
)
source_group("" FILES ${source})


set(typeSource
	type/Type.h
	type/Type.cpp
	type/Type.implementation.template.h
	type/TypeInfo.h
	type/TypeInfo.cpp
	type/TypeInfo.implementation.template.h
	type/Argument.h
	type/Argument.cpp
	type/Argument.implementation.template.h
)
source_group("type" FILES ${typeSource})
set(source ${source} ${typeSource})

set(valueSource
	value/DelegateValue.h
	value/DelegateValue.cpp
	value/IModifiableValue.h
	value/IModifiableValue.cpp
	value/IReadableValue.h
	value/IReadableValue.cpp
	value/ITypedModifiableValue.h
	value/ITypedModifiableValue.cpp
	value/ITypedReadableValue.h
	value/ITypedReadableValue.cpp
	value/ITypedSerializableValue.h
	value/ITypedSerializableValue.cpp
	value/ReferenceValue.h
	value/ReferenceValue.cpp
)
source_group("value" FILES ${valueSource})
set(source ${source} ${valueSource})



set(memberSource
	member/MemberInfo.h
	member/MemberInfo.cpp
	member/field/FieldInfo.h
	member/field/FieldInfo.cpp
	member/property/PropertyInfo.h
	member/property/PropertyInfo.cpp
	member/property/PropertySetInfo.h
	member/property/PropertySetInfo.cpp
	member/property/TypedPropertyInfo.h
	member/property/TypedPropertyInfo.cpp
	member/property/TypedPropertySetInfo.h
	member/property/TypedPropertySetInfo.cpp
	member/method/MethodInfo.h
	member/method/MethodInfo.cpp
	member/method/TypedMethodInfo.h
	member/method/TypedMethodInfo.cpp
	member/constructor/ConstructorInfo.h
	member/constructor/ConstructorInfo.cpp
	member/constructor/TypedConstructorInfo.h
	member/constructor/TypedConstructorInfo.cpp
)
source_group("member" FILES ${memberSource})
set(source ${source} ${memberSource})



set(preprocessorSource
preprocessor/properties.h
preprocessor/type.h
)
source_group("preprocessor" FILES ${preprocessorSource})
set(source ${source} ${preprocessorSource})




set(attributeSource
	attribute/Attribute.h
	attribute/Attribute.cpp
)
source_group("attribute" FILES ${attributeSource})
set(source ${source} ${attributeSource})


set(callableSource
	callable/Action.h
	callable/Action.cpp
	callable/DelegateAction.h
	callable/DelegateAction.cpp
	callable/Callable.h
	callable/Callable.cpp
	callable/CallableFunctor.h
	callable/CallableFunctor.cpp
)
source_group("callable" FILES ${callableSource})
set(source ${source} ${callableSource})


set(bindingSource
	binding/Binding.h
	binding/Binding.cpp
	binding/ValueConverter.h
	binding/ValueConverter.cpp
)
source_group("binding" FILES ${bindingSource})
set(source ${source} ${bindingSource})

set(dynamicSource
 ./dynamic/DynamicObject.h
 ./dynamic/DynamicObject.cpp
 ./dynamic/DynamicMappedObject.h
 ./dynamic/DynamicMappedObject.cpp
 ./dynamic/DynamicCallable.h
 ./dynamic/DynamicCallable.cpp
 ./dynamic/DynamicCallableImplementation.h
 ./dynamic/DynamicCallableImplementation.cpp
 ./dynamic/DynamicObjectImplementation.h
 ./dynamic/DynamicObjectImplementation.cpp
 ./dynamic/DynamicReflectedObjectImplementation.h
 ./dynamic/DynamicReflectedObjectImplementation.cpp

)
source_group("dynamics" FILES ${dynamicSource})
set(source ${source} ${dynamicSource})


set(adapterSource
	adapter/MemberAdapter.h
	adapter/MemberAdapter.cpp
	adapter/MethodAdapter.h
	adapter/MethodAdapter.cpp
	adapter/PropertyAdapter.h
	adapter/PropertyAdapter.cpp
)
source_group("adapter" FILES ${adapterSource})
set(source ${source} ${adapterSource})



set(typeSpecializationSource
 type/specialization/qualifierTypes.h
 type/specialization/fundementalTypes.h
 type/specialization/fundementalTypes.cpp
 type/specialization/stdTypes.h
 type/specialization/stdTypes.cpp


)
source_group("type\\specialization" FILES ${typeSpecializationSource})
set(source ${source} ${typeSpecializationSource})

set(namespaceSource
 namespace/NamespaceInfo.h
 namespace/NamespaceInfo.cpp
)
source_group("namespace" FILES ${namespaceSource})
set(source ${source} ${namespaceSource})

add_library(core.reflection ${source})
target_link_libraries(core.reflection core.property core.utility)