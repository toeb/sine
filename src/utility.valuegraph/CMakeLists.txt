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
 ./ChangeTracker.h
 ./ChangeTracker.cpp
 ./valuegraph.h 
 ./valuegraph.cpp
 
)

source_group("" FILES ${source})
add_library(utility.valuegraph ${source} CMakeLists.txt)
target_link_libraries(utility.valuegraph common)