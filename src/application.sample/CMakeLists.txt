

if(cmakeScriptsDirectory)
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL qtmain REQUIRED)
include(${cmakeScriptsDirectory}/UseSystemQt4.cmake)
include(${QT_USE_FILE})
endif(cmakeScriptsDirectory)


set(source
 Sample.h
 Sample.cpp
 SampleApplication.h
 SampleApplication.cpp 
../include/application.sample.h
)

source_group("" FILES ${source})

add_library(application.sample ${source} CMakeLists.txt)
target_link_libraries(application.sample 
	application.qt # add qt plugin application framework
	visualization.opengl.qt  # add qt visualization plugin
	simulation.runner.qt # add qt simulation runner
	simulation.time 	# add time
	 visualization
	visualization.opengl.renderer  #add general renderers
	visualization.opengl.renderer.geometry  # add geometry renderer
)