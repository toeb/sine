subdirlist(directories ${CMAKE_CURRENT_SOURCE_DIR})
list(REMOVE_ITEM directories ".svn")
list(REMOVE_ITEM directories "include")
set(dslibIgnoredProjects ${dslibIgnoredProjects} ".svn" "include" ".git")

foreach(item ${dslibIgnoredProjects})
	list(REMOVE_ITEM directories ${item}) 
endforeach(item ${dslibIgnoredProjects})

foreach(item ${directories})
 message(" adding: " ${item})
 add_subdirectory(${item})  
 if(TARGET ${item})
 if(NOT dslibProjectFolder STREQUAL "")
 project_folder(${dslibProjectFolder} ${item}) 
 endif(NOT dslibProjectFolder STREQUAL "")
 endif(TARGET ${item})
endforeach(item ${directories})



