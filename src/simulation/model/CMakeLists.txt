set(source 
 ./Connection.h
 ./Connection.cpp
 ./Connector.h
 ./Connector.cpp
 ./Model.h
 ./Model.cpp
 ./ModelElement.h
 ./ModelElement.cpp
 
)
source_group("" FILES ${source})
set(readerSource
  ./reader/ModelReader.h
  ./reader/ModelReader.cpp
)
set(source ${source} ${readerSource})
source_group("reader" FILES ${readerSource})

set(builderSource 
	./builder/IModelBuilder.h
	./builder/IModelBuilder.cpp
	./builder/ModelBuilderBase.h
	./builder/ModelBuilderBase.cpp
	./builder/ModelBuilderHolder.h	
)
set(source ${source} ${builderSource})
source_group("builder" FILES ${builderSource})

add_library(model ${source} CMakeLists.txt)
target_link_libraries(model core common)
project_folder("simulation/modules" model)