#include <core.testing.h>

#include <core.reflection/type/Argument.h>

typedef nspace::Argument Argument;

UNITTEST(Argumentcreateinvalid){
    // a default constructed argument is invalid
    Argument a;
    CHECK(!(bool)a.isValid());
    CHECK(!(bool)a.data);
    CHECK(!a.type);    
}



UNITTEST(Argumentcreatesimple){
    // a default constructed argument is invalid
    Argument a = 2;
    CHECK((bool)a.isValid());
    CHECK((bool)a.data);
    CHECK(a.type);    
    CHECK_EQUAL(nspace::type_of<int>(),a.type);    
}