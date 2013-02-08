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

./Comparator.h
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
target_link_libraries(core)
