#include "IMeshBuilder.h"


using namespace nspace;

void IMeshBuilder::begin(){}
void IMeshBuilder::position(Vector3D && position){}
void IMeshBuilder::normal(Vector3D && normal){}
void IMeshBuilder::textureCoordinates(Vector3D && tex){}
void IMeshBuilder::material(std::string && material){}
void IMeshBuilder::materialLibrary(std::string && library){}
void IMeshBuilder::group( std::string && name){}
void IMeshBuilder::object( std::string && object){}
void IMeshBuilder::face(FaceType && face){}
void IMeshBuilder::end(){}


MeshFaceVertex::MeshFaceVertex():position(0),normal(0),textureCoordinates(0){}
MeshFace::MeshFace():smoothingGroup(0),object(0),material(0){}
MeshElement::MeshElement():index(0){}