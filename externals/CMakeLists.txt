# specifiy needed external here
set(useExternals
lodepng tinyxml2 rply freeglut cppunitlite lua
)
# iterate through all external, add them and put them in externals project folder
foreach(item ${useExternals})
 message("external added: " ${item})
 add_subdirectory(${item})
 if(TARGET ${item})
  if(NOT dslibExternalsProjectFolder STREQUAL "")
    project_folder(${dslibExternalsProjectFolder} ${item}) 
  endif(NOT dslibExternalsProjectFolder STREQUAL "")
 endif(TARGET ${item})
endforeach(item ${useExternals})

