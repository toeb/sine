#pragma once
#include <core/utilities/Preprocessor.h>


#define DS_FOR_DEFAULT_TYPE_LIST(ACTION)\
  ACTION(bool)\
  ACTION(int)\
  ACTION(void*)\
  ACTION(std::shared_ptr<int>)\
  ACTION(std::string)\
  ACTION(std::vector<std::string>)\
  ACTION(nspace::Object*)\
  ACTION(nspace::Object)

#define DS_UNIT_TEST_RESULT(SUCCESS, MESSAGE) nspace::UnitTestResult(SUCCESS,MESSAGE,DS_SOURCE_INFO_PTR())
#define DS_UNIT_TEST_REPORT(SUCCESS, MESSAGE) {Results().add(new DS_UNIT_TEST_RESULT(SUCCESS,MESSAGE));}
#define DS_UNIT_TEST_REPORT_FAILURE(MESSAGE) DS_UNIT_TEST_REPORT(true,MESSAGE)
#define DS_UNIT_TEST_REPORT_SUCCESS(MESSAGE) DS_UNIT_TEST_REPORT(false,MESSAGE)

  
#define DS_UNIT_TEST_CHECK(condition)\
{ if (!(condition)) \
  {  DS_UNIT_TEST_REPORT_FAILURE(DS_INLINE_STRING("condition not met: '"<<#condition<<"'")); return; } }
  
#define DS_UNIT_TEST_CHECK_EQUAL(expected,actual)\
{ if (!((expected) == (actual)))  DS_UNIT_TEST_REPORT_FAILURE(DS_INLINE_STRING(#actual<<"("<<(actual)<<")!="<<#expected<<"("<< (expected)<<")"));}


#define DS_UNIT_TEST_LONGS_EQUAL(expected,actual)\
{ long actualTemp = actual; \
  long expectedTemp = expected; \
  DS_UNIT_TEST_CHECK_EQUAL(expectedTemp,actualTemp);}



#define DS_UNIT_TEST_DOUBLES_EQUAL(expected,actual,threshold)\
{ double actualTemp = actual; \
  double expectedTemp = expected; \
  if (fabs((expectedTemp)-(actualTemp)) > (threshold)) \
  { DS_UNIT_TEST_REPORT_FAILURE(DS_INLINE_STRING("|"<<#actual<<"("<<(actualTemp)<<")-"<<#expected<<"("<<(expectedTemp)<<")| >"<<#threshold<<"("<< double(threshold)<<")")); }}

#define DS_UNIT_TEST_FAIL(MESSAGE)\
  {DS_UNIT_TEST_REPORT_FAILURE(DS_INLINE_STRING(MESSAGE));}

//todo
//#define DS_UNIT_TEST_INCONCLUSIVE(MESSAGE)  {DS_UNIT_TEST_REPORT(DS_INLINE_STRING(MESSAGE));}


#define DS_TESTCLASSNAME(NAME) Test##NAME##Class
#define DS_TESTINSTANCENAME(NAME) Test##NAME##Instance

#define DS_TEST_PERFORMANCE(NAME) \
class DS_TESTCLASSNAME(NAME) : public nspace::TypedPerformanceTest<DS_TESTCLASSNAME(NAME)>{\
public:inline void test();\
  typedef DS_TESTCLASSNAME(NAME) UnitTestClass;\
  DS_TESTCLASSNAME(NAME):UnitTest(#NAME){nspace::UnitTestRunner::instance()->RegisteredTests().add(this);}\
}DS_TESTINSTANCENAME(NAME);\
  void DS_TESTCLASSNAME(NAME)::test()

#define DS_TEST(NAME) \
class DS_TESTCLASSNAME(NAME) : public nspace::UnitTest{\
public:inline void test();\
  typedef DS_TESTCLASSNAME(NAME) UnitTestClass;\
  DS_TESTCLASSNAME(NAME)():UnitTest(#NAME){nspace::UnitTestRunner::instance()->RegisteredTests().add(this);}\
}DS_TESTINSTANCENAME(NAME);\
  void DS_TESTCLASSNAME(NAME)::test()
#define DS_ADD_TYPENAME_QUALIFIER(X) typename X

#define DS_TEST_TEMPLATED_DEFINITION(NAME,...)\
  template<DS_REDUCE_COMMA(DS_ADD_TYPENAME_QUALIFIER,__VA_ARGS__)>\
class DS_TESTCLASSNAME(NAME) : public nspace::UnitTest{\
private:\
 std::string templateArguments;\
public:inline void test();\
  typedef DS_TESTCLASSNAME(NAME) UnitTestClass;\
  DS_TESTCLASSNAME(NAME)(const std::string & templateArguments):UnitTest(#NAME),templateArguments(templateArguments){setTestName(DS_INLINE_STRING(#NAME<<"<"<<templateArguments<<">"));nspace::UnitTestRunner::instance()->RegisteredTests().add(this);}\
};

#define DS_TEST_TEMPLATED_IMPLEMENTATION(NAME,...) template<DS_REDUCE_COMMA(DS_ADD_TYPENAME_QUALIFIER,__VA_ARGS__)> void DS_TESTCLASSNAME(NAME)<DS_REDUCE_COMMA(DS_NOOP,__VA_ARGS__)>::test()
  
#define DS_TEST_TEMPLATED(NAME,...)\
  DS_TEST_TEMPLATED_DEFINITION(NAME,__VA_ARGS__)\
  DS_TEST_TEMPLATED_IMPLEMENTATION(NAME,__VA_ARGS__)


#define DS_TEST_TEMPLATED_INSTANCE(NAME,...) namespace NAME##TemplateTests{  DS_TESTCLASSNAME(NAME)  <__VA_ARGS__>  DS_CONCAT(Test,__COUNTER__)(#__VA_ARGS__);  }


//rename
#define DS_TEST_TEMPLATED_INSTANCIATE(TYPE) <TYPE>  DS_CONCAT(Test,__COUNTER__)(#TYPE);


#define DS_TEMPLATED_DEFAULT_TESTS(NAME,...) DS_TEST_TEMPLATED_DEFINITION(NAME,__VA_ARGS__) \
  namespace NAME##TemplateTests { \
  DS_FOR_DEFAULT_TYPE_LIST(DS_TESTCLASSNAME(NAME) DS_TEST_TEMPLATED_INSTANCIATE) \
} \
  DS_TEST_TEMPLATED_IMPLEMENTATION(NAME,__VA_ARGS__)

#ifndef UNITTEST
#define UNITTEST(NAME) DS_TEST(NAME)
#endif

#ifndef TEST
#define TEST(NAME,NAME2) DS_TEST(NAME2##NAME)
#endif

#ifndef TTEST
#define TTEST(NAME,...)  DS_TEST_TEMPLATED(NAME,__VA_ARGS__)
#endif

#ifndef TTEST_INSTANCE
#define TTEST_INSTANCE(NAME,...)DS_TEST_TEMPLATED_INSTANCE(NAME,__VA_ARGS__)
#endif

#ifndef TTEST_DEFAULT
#define TTEST_DEFAULT(NAME,...) DS_TEMPLATED_DEFAULT_TESTS(NAME,__VA_ARGS__)
#endif


#ifndef PTEST
#define PTEST(NAME) DS_TEST_PERFORMANCE(NAME)
#endif
  
#ifndef FAIL
#define FAIL(MESSAGE) DS_UNIT_TEST_FAIL(MESSAGE)
#endif

#ifndef CHECK
#define CHECK(condition) DS_UNIT_TEST_CHECK(condition)
#endif

#ifndef CHECK_EQUAL
#define CHECK_EQUAL(expected, actual) DS_UNIT_TEST_CHECK_EQUAL(expected, actual)
#endif
  
#ifndef LONGS_EQUAL
#define LONGS_EQUAL(expected, actual) DS_UNIT_TEST_LONGS_EQUAL(expected, actual)
#endif

#ifndef DOUBLES_EQUAL
#define DOUBLES_EQUAL(expected, actual,threshold) DS_UNIT_TEST_DOUBLES_EQUAL(expected, actual,threshold)
#endif
