set(source
 ./ConsoleRunner.h
 ./ConsoleRunner.cpp
)
source_group("src" FILES ${source})
add_library(consolerunner  ${source})
target_link_libraries(consolerunner runner)
project_folder("runners" consolerunner)