
set(source
./Time.h
./Time.cpp
./Object.h
./Object.cpp
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
./Property.h
./Property.cpp
./TypedProperty.h
./TypedProperty.cpp
./Reflection.h
../config.h
../core.h
)
source_group("" FILES ${source})

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
add_library(core ${source} ${patternsSource} CMakeLists.txt)

