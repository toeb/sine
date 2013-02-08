#subdirs(math core.base simulation core.hub core core.collection simulation.geometry.mesh core.reflection core.properties core.template core.preprocessor utility.scripting.lua core.testing)


subdirlist(directories ${CMAKE_CURRENT_SOURCE_DIR})
list(REMOVE_ITEM directories ".svn")
list(REMOVE_ITEM directories ".git")

foreach(item ${directories})
 message("  adding test: " ${item})
 add_subdirectory(${item})  
 if(TARGET ${item})
 project_folder("test" ${item})  
 add_test(NAME ${item} COMMAND ${item})
 endif(TARGET ${item})
endforeach(item ${directories})


 
