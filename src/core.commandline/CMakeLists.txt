set(source ../include/core.commandline.h )




set(commandlineParserSource
  ./CommandLineParser.h
  ./CommandLineParser.cpp
  ./CommandLineArgumentDefinition.h
  ./CommandLineArgumentDefinition.cpp
  ./CommandLineArgument.h
  ./CommandLineArgument.cpp
)
source_group("commandline" FILES ${commandlineParserSource})

set(source ${source} ${commandlineParserSource})

source_group("patterns" FILES ${patternsSource})

add_library(core.commandline  ${source} CMakeLists.txt)
target_link_libraries(core.commandline core.property)


