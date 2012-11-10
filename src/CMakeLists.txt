subdirlist(directories ${CMAKE_CURRENT_SOURCE_DIR})
list(REMOVE_ITEM directories ".svn")
list(REMOVE_ITEM directories "include")
set(dslibIgnoredProjects ${dslibIgnoredProjects} ".svn" "include")

foreach(item ${dslibIgnoredProjects})
	list(REMOVE_ITEM directories ${item}) 
endforeach(item ${dslibIgnoredProjects})

foreach(item ${directories})
 message(" adding: " ${item})
 add_subdirectory(${item})  
 if(TARGET ${item})
 if(${rootProjectFolder})
 project_folder(${rootProjectFolder} ${item})
 endif(${rootProjectFolder})
 endif(TARGET ${item})
endforeach(item ${directories})



