set(source )



set(graphSource
../include/core.graph.h
./graph/TypedNode.h
./graph/DataNode.h
./graph/DerivableDataNode.h
./graph/Node.h
./graph/Node.cpp
./graph/Graph.h
./graph/Graph.cpp
)
source_group("" FILES ${graphSource})
add_library(core.graph  ${source} CMakeLists.txt)
target_link_libraries(core.graph core)

