set(source
 ./Value.h
 ./Value.cpp
 ./CachedValue.h
 ./CachedValue.cpp
 ./DependentValue.h
 ./DependentValue.cpp
 ./TypedObservableValue.h
 ./TypedObservableValue.cpp
 ./TypedValue.h
 ./TypedValue.cpp
 ./ValueHistory.h
 ./ValueHistory.cpp
 ./ObservableValue.h
 ./ObservableValue.cpp
 ./valuegraph.h 
 ./valuegraph.cpp
 
)

source_group("" FILES ${source})
add_library(valuegraph ${source} CMakeLists.txt)
project_folder("utility" valuegraph)
target_link_libraries(valuegraph common)