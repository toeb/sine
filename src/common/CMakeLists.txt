configure_file(Config.in Config.h)
set(source
	./Types.h
	./Time.h
	./Time.cpp
	./Config.h
	./Object.h
)
source_group("src" FILES ${source})

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
add_library(common ${source} ${patternsSource} CMakeLists.txt)
project_folder("" common)