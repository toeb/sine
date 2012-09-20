set(source
 ./ConsoleRunner.h
 ./ConsoleRunner.cpp
)
source_group("src" FILES ${source})
add_library(simulation.runner.console  ${source})
target_link_libraries(simulation.runner.console simulation.runner)