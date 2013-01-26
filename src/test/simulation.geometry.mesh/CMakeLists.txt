set(source
	tests.cpp
	main.cpp 
)
 source_group("" FILES ${source})
 add_executable(test.simulation.geometry.mesh ${source} CMakeLists.txt)
 target_link_libraries(test.simulation.geometry.mesh core.testing  utility.reader core core.task  utility.reader.obj utility.reader.mtl utility.reader.ply)
 project_folder("test" test.simulation.geometry.mesh )

 
 add_test(NAME test.simulation.geometry.mesh COMMAND test.simulation.geometry.mesh)