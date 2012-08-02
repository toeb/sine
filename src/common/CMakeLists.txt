
set(source
./Types.h
 ./Time.h
 ./Time.cpp
 ./Config.h
)
source_group("src" FILES ${source})

set(patternsSource
	./patterns/ITask.h
	./patterns/TaskRunner.h
	./patterns/TaskRunner.cpp
	./patterns/ValueHolder.h
	./patterns/Composite.h
)
source_group("src\\patterns" FILES ${patternsSource})
add_library(common ${source} ${patternsSource} CMakeLists.txt)
project_folder("" common)