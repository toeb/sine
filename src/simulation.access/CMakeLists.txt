set(source
	./TypedValueDelegate.h
	./TypedValueDelegate.cpp
	./TypedValue.h
	./TypedValue.cpp
	./TypedMatrixValue.h
	./TypedMatrixValue.cpp
	./MatrixValue.h
	./MatrixValue.cpp
	./IValue.h
	./IValue.cpp
	./IAction.h
	./IAction.cpp
	./IComponent.h
	./DelegateAction.h
	./DelegateAction.cpp
)
source_group("" FILES ${source})
add_library(simulation.access ${source} CMakeLists.txt)
target_link_libraries(simulation.access  simulation)