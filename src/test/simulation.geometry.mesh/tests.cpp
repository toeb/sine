#include <CppUnitLite/TestHarness.h>
#include <math/core.h>
#include <math.matrix.h>
#include <math.matrix.dslib/core.h>
#include <visualization/Material.h>

#include <utility.reader.h>
#include <utility.reader.ply.h>
#include <utility.reader.obj.h>
#include <utility.reader.mtl.h>
#include <map>
#include <simulation.geometry/mesh/MeshOperations.h>
#include <iostream>
#include <fstream>
#include <core/patterns/Multiton.h>

#include <core.fsm/HierarchicalFiniteStateMachine.h>
using namespace nspace;

/*
TEST(7, MeshBuilder){
  
}

TEST(7, CustomMesh){
  CustomMesh uut;
  uut.setFaceCount(10);
  uut.setVertexCount(11);
  uut.initialize();
  uut.vertex(0).position() = Vector3D(1,0,0);
  auto vertex = meshVertexGet(uut,0);
  auto result = isSameType(vertex,CustomVertex(0,uut));

  CHECK(result);

}

TEST(1,Test){
  MyVertex v;
  setVertexPosition(v,Vector3D(1,0,0));
  CHECK(v.position(0,0)==1);
}


TEST(2,CustomMesh){
  CustomMesh myMesh;
  auto result = isSameType<MESH_VERTEX_INDEX_TYPE(CustomMesh), size_t>();
  CHECK(result);
}
TEST(3, CustomMesh){
  CustomMesh myMesh;
  auto result = isSameType<MESH_VERTEX_TYPE(CustomMesh), CustomVertex>();
  CHECK(result);
}
TEST(4, CustomMesh){
  CustomMesh myMesh;
  auto result = meshVertexCount(myMesh);
  CHECK(result==0);
}
TEST(5, CustomMesh){
  CustomMesh myMesh;
  myMesh.setVertexCount(40);
  auto result = meshVertexCount(myMesh);
  CHECK(result==40);
}
TEST(6, CustomMesh){
  {
    CustomMesh uut;
    uut.setVertexCount(1);
    uut.initialize();
    uut.vertex(0).position()=Vector3D::UnitY();
    auto result = meshVertexGet(uut,0);
    CHECK(result.index == 0);
    CHECK(&result.mesh ==&uut);
    CHECK(result.position()(2)==0);
    CHECK(result.position()(1)==1);
    CHECK(result.position()(0)==0);
  }
}
*/

class A: public Object{
  TYPED_OBJECT(A);
public:
  std::string asd(){return "das";}
};
class B : public Object{
  TYPED_OBJECT(B);

};

TEST(1,Multiton){
  Multiton<Object> uut;
  auto a = uut.request<A>();
  CHECK(a==0);
}
TEST(2,Multiton){
  
  Multiton<Object> uut;
  auto a = uut.require<A>();
  CHECK(a!=0);
}
TEST(3,Multiton){
  Multiton<Object> uut;  
  uut.registerType<B>();
  auto b = uut.request<B>();
  CHECK(b!=0);
}
TEST(4,Multiton){
  Multiton<Object> uut;
  auto aa = uut.require<A>();
  auto ab=uut.require<A>();

  CHECK(aa==ab);
}


//  string ply="ply\ncomment asd ddad awd adwd adw d aw \nelement 1000 vertex\n";
//
/*
TEST(1,PLY){
  using namespace std;
  string ply="ply";
  istringstream iss(ply);
  PlyStateMachine uut;

  PlyToken token(iss);  
  while(token.next()){
    uut.process(token);
  }

  auto state = uut.leafState();
  CHECK(&state->getType()==typeof(HeaderState));
  
}


TEST(2,PLY){
  using namespace std;
  string ply="plyalei";
  istringstream iss(ply);
  PlyStateMachine uut;

  PlyToken token(iss);  
  while(token.next()){
    uut.process(token);
  }

  auto state = uut.leafState();
  CHECK(&state->getType()==typeof(BadFileState));  
}



TEST(3,PLY){
  using namespace std;
  string ply="plyalei";
  istringstream iss(ply);
  PlyStateMachine uut;
  IMeshBuilder builder;
  uut.setBuilder(&builder);
  PlyToken token(iss);  
  while(token.next()){
    uut.process(token);
  }


  auto state = uut.leafState();
  CHECK(state->getBuilder()==&builder);  
}


TEST(4,PLY){
  using namespace std;
  string ply="ply\ncomment hellasda asdasd asd asd as dasd asd asd as das asd\n";
  istringstream iss(ply);
  PlyStateMachine uut;
  IMeshBuilder builder;
  uut.setBuilder(&builder);
  PlyToken token(iss);  
  while(token.next()){
    uut.process(token);
  }
  CHECK(&uut.leafState()->getType()==typeof(HeaderState));
  CHECK(uut.getPlyObject()->comments.size()==1);  
}


TEST(5,PLY){
  using namespace std;
  string ply="ply\ncomment hellasda asdasd asd asd as dasd asd asd as das asd\nelement vertex 100";
  istringstream iss(ply);
  PlyStateMachine uut;
  IMeshBuilder builder;
  uut.setBuilder(&builder);
  PlyToken token(iss);  
  while(token.next()){
    uut.process(token);
  }
  
  CHECK(&uut.leafState()->getType()==typeof(HeaderState));
  CHECK(uut.getPlyObject()->size()==1);  
}

TEST(6,PLy){
  using namespace std;
    string ply="ply\ncomment hellasda asdasd asd asd as dasd asd asd as das asd\nelement vertex 100";
  istringstream iss(ply);
  PlyObject o;
  IMeshBuilder b;
  ply2::PlyFiniteStateMachine uut(o,b);
  PlyToken token(iss);  
  while(token.next()){
    uut.process(token);
  }
}
*/

TEST(1,PLY){
  PlyReader reader;
  IMeshBuilder builder;
  reader.setBuilder(&builder);
 // reader.readFile("meshes/ply/blade.ply");

}
TEST(1, MtlReader){
  MtlReader reader;
  bool result = reader.readFile("materials/mtl/example.mtl");
  CHECK(result);
}

TEST(1, ObjReader){
  ObjReader obj;
  
  IMeshBuilder builder;
  obj.setBuilder(&builder);
  obj.readFile("meshes/obj/alfa147.obj");
}

/*
TEST(LoadPly, MeshReader){
  PlyReader reader;
  
  auto result = reader.readFile("meshes/ply/horse.ply");

  CHECK(result);
}*/

TEST(LoadObj, MeshReader){


}


