
set(source
	
# reflection.cpp
# type.cpp
# argument.cpp
# methodinfo.cpp
# constructorinfo.cpp
# propertyinfo.cpp
# namespaceinfo.cpp
# propertyadapter.cpp
 uninvasive.cpp
# callable.cpp
# attribute.cpp
# methodadapter.cpp
# memberadapter.cpp
# dynamicobject.cpp
 #copeinfo.cpp
 )
 source_group("" FILES ${source})
 add_executable(test.core.reflection ${source} CMakeLists.txt)
 target_link_libraries(test.core.reflection application.console.testing core.logging core )
 project_folder("test" test.core.reflection )
 
 add_test(NAME test.core.reflection COMMAND test.core.reflection)