#include <core.testing.h>

#include <core.reflection/type/Argument.h>

using namespace nspace;



UNITTEST(Argumentcreateinvalid){
    // a default constructed argument is invalid
    Argument a;
    CHECK(!(bool)a.isValid());
    CHECK(!(bool)a.data);
    CHECK(!a.type);    
}



UNITTEST(Argumentcreatesimple){
    Argument a = 2;
    CHECK((bool)a.isValid());
    CHECK((bool)a.data);
    CHECK(a.type);    
    CHECK_EQUAL(nspace::type_of<int>(),a.type);    
}


UNITTEST(ComplexArgument){
  std::shared_ptr<int> sptr(new int(32));
  Argument arg =sptr;
  std::shared_ptr<int> b = arg;
  auto ptr = b.get();
  CHECK(ptr==sptr.get());
}

