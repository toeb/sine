set(source
./UrdfModelReader.h
./UrdfModelReader.cpp
)
source_group("" FILES ${source})
set(parsersSource
./parsers/PrimitiveParsers.h
./parsers/RootParser.h
./parsers/AxisParser.h
./parsers/ChildLinkParser.h
./parsers/ConnectionParser.h
./parsers/ConnectionTypeParser.h
./parsers/ConnectorParser.h
./parsers/ConnectParser.h
./parsers/GeometryParser.h
./parsers/InertialFrameParser.h
./parsers/VisualParser.h
./parsers/JointParser.h
./parsers/LinkParser.h
./parsers/InertiaParser.h
./parsers/MassConfigurationParser.h
./parsers/MassParser.h
./parsers/MaterialParser.h
./parsers/OriginParser.h
./parsers/ParentLinkParser.h
./parsers/RobotElementParser.cpp
./parsers/RobotElementParser.h
./parsers/UrdfExtensionParser.h
)
source_group("parsers" FILES ${parsersSource})
set(source ${source} ${parsersSource})

set(structsSource
	./structs/MassConfiguration.h
	./structs/UrdfOrigin.h
	./structs/UrdfConnection.h
	./structs/UrdfConnector.h
	./structs/UrdfElement.h
	./structs/UrdfJoint.h
	./structs/UrdfLink.h
)
source_group("structs" FILES ${structsSource})
set(source ${source} ${structsSource})



add_library(urdf ${source} CMakeLists.txt)
target_link_libraries(urdf model kinematics xml)
project_folder("readers" urdf)

