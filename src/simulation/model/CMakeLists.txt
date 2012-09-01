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
  ./ModelReader.h
  ./ModelReader.cpp
)
set(source ${source} ${readerSource})
source_group("reader" FILES ${readerSource})

set(builderSource 
	./IModelBuilder.h
	./IModelBuilder.cpp
	./ModelBuilderBase.h
	./ModelBuilderBase.cpp
	
)
set(source ${source} ${builderSource})
source_group("builder" ${builderSource})

add_library(model ${source} CMakeLists.txt)
target_link_libraries(model core common)
project_folder("simulation/modules" model)
subdirs(builder reader)