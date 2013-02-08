set(source ../include/core.commandline.h )




set(commandlineParserSource
  ./commandline/CommandLineParser.h
  ./commandline/CommandLineParser.cpp
  ./commandline/CommandLineArgumentDefinition.h
  ./commandline/CommandLineArgumentDefinition.cpp
  ./commandline/CommandLineArgument.h
  ./commandline/CommandLineArgument.cpp
)
source_group("commandline" FILES ${commandlineParserSource})

set(source ${source} ${commandlineParserSource})

source_group("patterns" FILES ${patternsSource})

add_library(core.commandline core.properties ${source} CMakeLists.txt)


