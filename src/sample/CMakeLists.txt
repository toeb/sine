
set(directories 
sample.application.qt
 sample.mesh.render 
 sample.particlesystem 
 sample.threading 
 sample.mathgl
 sample.simple 
 sample.qt.plugins 
 qtsample imaging
 glutsample
 mathperformance
 simulationperformance 
 valuegraphsample
 sample.matrix
 sample.empty
 sample.reflection)
#subdirlist(directories ${CMAKE_CURRENT_SOURCE_DIR})
#list(REMOVE_ITEM directories ".svn")
#list(REMOVE_ITEM directories "include")
foreach(item ${directories})
 message("  adding: " ${item})
 add_subdirectory(${item}) 
endforeach(item ${directories})

