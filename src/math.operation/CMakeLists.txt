set(source 
./CMakeLists.txt
./BinaryOperation.h
./NullaryOperation.h
./Operation.h
./Operation.cpp
./UnaryOperation.h
)

source_group("" FILES ${source})
add_library(math.operation ${source})

target_link_libraries(math.operation core)