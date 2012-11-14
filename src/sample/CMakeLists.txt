
set(directories sample.threading sample.simple sample.qt.plugins qtsample imaging glutsample mathperformance simulationperformance valuegraphsample sample.scripting)
#subdirlist(directories ${CMAKE_CURRENT_SOURCE_DIR})
#list(REMOVE_ITEM directories ".svn")
#list(REMOVE_ITEM directories "include")
foreach(item ${directories})
 message("  adding: " ${item})
 add_subdirectory(${item}) 
endforeach(item ${directories})

