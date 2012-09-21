
set(source
./Types.h
./Time.h
./Time.cpp
./Object.h
./Object.cpp
./NamedObject.h
./NamedObject.cpp
./Node.h
./Node.cpp
./Graph.h
./Comparator.h
./ObservableCollection.h
./Query.h
./Set.h
./StringTools.h
./StringTools.cpp
./ValueLookup.h
./ValueLookup.cpp
../config.h
)
source_group("" FILES ${source})

set(patternsSource
./patterns/ITask.h
./patterns/TaskRunner.h
./patterns/TaskRunner.cpp
./patterns/ValueHolder.h
./patterns/Composite.h
./patterns/ArrayPool.h
./patterns/Visitor.h
./patterns/Singleton.h
./patterns/Decorator.h
)
source_group("src\\patterns" FILES ${patternsSource})
add_library(core ${source} ${patternsSource} CMakeLists.txt)

