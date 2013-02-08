set(source )



set(graphSource
../include/core.graph.h
./TypedNode.h
./DataNode.h
./DerivableDataNode.h
./Node.h
./Node.cpp
./Graph.h
./Graph.cpp
)
source_group("" FILES ${graphSource})
set(source ${source} ${graphSource})
add_library(core.graph  ${source} CMakeLists.txt)
target_link_libraries(core.graph core)

