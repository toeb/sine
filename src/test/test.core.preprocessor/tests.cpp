#include <core.testing.h>
#include <map>
#include <string>

#include <core/patterns/StaticInitializer.h>

UNITTEST(DS_MINUS_ONE){
  int result  = DS_MINUS_ONE(15);
  CHECK_EQUAL(14,result);
}

UNITTEST(DS_SEQUENCE){
  int result[10]  = {DS_SEQUENCE(9)};
  for(int i=0; i < 10; i++){
    CHECK_EQUAL(i,result[i]);
  }
}



UNITTEST(DS_REDUCE){
#define my_op +
  int i = DS_REDUCE(,my_op,1,1,1,1,1,1);
  CHECK_EQUAL(6,i);
#undef my_op
}


UNITTEST(DS_REDUCE_N){
#define my_op +
  int i = DS_REDUCE_N(5,,my_op,1,1,1,1,1);
  CHECK_EQUAL(5,i);
#undef my_op
}

UNITTEST(DS_REDUCE_3){
#define my_op +
  int i = DS_REDUCE_3(,my_op,2,3,4);
  CHECK_EQUAL(9,i);
#undef my_op
}

UNITTEST(DS_REDUCE_2){
#define my_op +
  int i = DS_REDUCE_2(,my_op,2,3);
  CHECK_EQUAL(5,i);
#undef my_op
}

UNITTEST(DS_REDUCE_1){
#define my_op +
  int i = DS_REDUCE_1(,my_op,2);
  CHECK_EQUAL(2,i);
#undef my_op
}

UNITTEST(DS_NUM_ARGS1){
  int i= DS_NUM_ARGS(a ,b, c, 3, 4, 5,1, 2, asdasd);
  CHECK_EQUAL(9,i);
}

UNITTEST(DS_NUM_ARGS2){
  int i = DS_NUM_ARGS();
  //todo.  implement DS_NUM_ARGS to work for 0
  //CHECK_EQUAL(0,i);

}


UNITTEST(DS_FOREACH){
  int x=0;
#define MY_OP(X) x++;
  DS_FOREACH(MY_OP,x,x,x,x,x,x,x,x,x);
  CHECK_EQUAL(9,x);

#undef MY_OP

}

UNITTEST(DS_FOREACH_N){
  int x=0;
#define MY_OP(X) x++;
  DS_FOREACH_N(7,MY_OP,x,x,x,x,x,x,x);
  CHECK_EQUAL(7,x);

#undef MY_OP

}

UNITTEST(DS_FOREACH_10) {
  int x=0;
#define MY_OP(X) x++;
  DS_FOREACH_10(MY_OP,x,x,x,x,x,x,x,x,x,x);
  CHECK_EQUAL(10,x);

#undef MY_OP
}

UNITTEST(DS_FOREACH_1){
  int x=2;

#define MY_OP(X) X=X*X;
  DS_FOREACH_1(MY_OP,x)

    CHECK_EQUAL(x,4);
#undef MY_OP
}

UNITTEST(DS_FOREACH_2){
  int x=2;
  int y=3;
#define MY_OP(X) X=X*X;
  DS_FOREACH_2(MY_OP,x,y);

  CHECK_EQUAL(x,4);
  CHECK_EQUAL(y,9);
#undef MY_OP
}

UNITTEST(DS_FOREACH_3){
  int x=2;
#define MY_OP(X) X=X*X;
  DS_FOREACH_3(MY_OP,x,x,x);

  CHECK_EQUAL(x,256);
#undef MY_OP
}
UNITTEST(DS_FIRST){
  int i=0;
  int j=0;
  int k=0;

  DS_FIRST(i++;,j++;,k++;);
  CHECK_EQUAL(1,i);
  CHECK_EQUAL(0,j);
  CHECK_EQUAL(0,k);

}

UNITTEST(DS_STRINGIFY){
  const char * cstr= DS_STRINGIFY(int);
  CHECK_EQUAL(std::string("int"),std::string(cstr));

}

UNITTEST(DS_REST){
  int ar[3] = {DS_REST(1,2,3,4)};

  CHECK_EQUAL(ar[0],2);
  CHECK_EQUAL(ar[1],3);
  CHECK_EQUAL(ar[2],4);
}

UNITTEST(DS_EXECUTE_ONCE1){
  static bool wasExecuted = false;
  struct A{
    DS_ONCE{
      wasExecuted = true;
    }
  }a;
  CHECK(wasExecuted);
}

struct ExecuteOnce2TestStruct{
  DS_EXECUTE_ONCE(SectionA);
  
}__executeOnce2TestInstance;// up to now atleast one instance per class has to be created for execute_once to have occured
bool wasExecuteOnce2TestCalled=false;
// source code implementation of execute once / static initializer is allowed
void ExecuteOnce2TestStruct::DS_EXECUTE_ONCE_IMPLEMENTATION(SectionA){
  wasExecuteOnce2TestCalled=true;
}

UNITTEST(DS_EXECUTE_ONCE2){
  CHECK(wasExecuteOnce2TestCalled);
}