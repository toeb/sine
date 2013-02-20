set(source 
	./CMakeLists.txt
	./DefaultTypes.h
	./DefaultTypes.cpp
	../include/core.reflection.h
)
source_group("" FILES ${source})


set(typeSource
	type/Type.h
	type/Type.cpp
	type/Type.implementation.h
	type/TypeInfo.h
	type/TypeInfo.cpp
	type/Argument.h
	type/Argument.cpp
	type/TypeRepository.h
	type/TypeRepository.cpp
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
)
source_group("member" FILES ${memberSource})
set(source ${source} ${memberSource})



set(preprocessorSource
preprocessor/properties.h

)
source_group("preprocessor" FILES ${preprocessorSource})
set(source ${source} ${preprocessorSource})




set(attributeSource
	attribute/Attribute.h
	attribute/Attribute.cpp
)
source_group("attribute" FILES ${attributeSource})
set(source ${source} ${attributeSource})


set(actionSource
	action/Action.h
	action/Action.cpp
	action/DelegateAction.h
	action/DelegateAction.cpp
	action/MethodAction.h
	action/MethodAction.cpp
)
source_group("action" FILES ${actionSource})
set(source ${source} ${actionSource})


set(bindingSource
	binding/Binding.h
	binding/Binding.cpp
	binding/ValueConverter.h
	binding/ValueConverter.cpp
)
source_group("binding" FILES ${bindingSource})
set(source ${source} ${bindingSource})



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


add_library(core.reflection ${source})
target_link_libraries(core.reflection core core.property core.serialization)