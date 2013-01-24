#pragma once
#include <core/utilities/Preprocessor.h>

#define DS_UNIT_TEST_RESULT(SUCCESS, MESSAGE) nspace::UnitTestResult(SUCCESS,MESSAGE,DS_SOURCE_INFO_PTR())
#define DS_UNIT_TEST_REPORT(SUCCESS, MESSAGE) {Results().add(new DS_UNIT_TEST_RESULT(SUCCESS,MESSAGE));}
#define DS_UNIT_TEST_REPORT_FAILURE(MESSAGE) DS_UNIT_TEST_REPORT(true,MESSAGE)
#define DS_UNIT_TEST_REPORT_SUCCESS(MESSAGE) DS_UNIT_TEST_REPORT(false,MESSAGE)

#define DS_INLINE_STRING(ARGS) std::function<std::string ()>([&]()->std::string{std::ostringstream stream; stream << ARGS; return stream.str();})() 
  
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



#define DS_TESTCLASSNAME(NAME) Test##NAME##Class
#define DS_TESTINSTANCENAME(NAME) Test##NAME##Instance

#define DS_TEST_PERFORMANCE(NAME) \
class DS_TESTCLASSNAME(NAME) : public nspace::TypedPerformanceTest<DS_TESTCLASSNAME(NAME)>{\
public:inline void test();\
  DS_TESTCLASSNAME(NAME):UnitTest(#NAME){nspace::UnitTestRunner::instance()->RegisteredTests().add(this);}\
}DS_TESTINSTANCENAME(NAME);\
  void DS_TESTCLASSNAME(NAME)::test()

#define DS_TEST(NAME) \
class DS_TESTCLASSNAME(NAME) : public nspace::UnitTest{\
public:inline void test();\
  DS_TESTCLASSNAME(NAME)():UnitTest(#NAME){nspace::UnitTestRunner::instance()->RegisteredTests().add(this);}\
}DS_TESTINSTANCENAME(NAME);\
  void DS_TESTCLASSNAME(NAME)::test()


/*#ifndef TEST(NAME) 
#define TEST(NAME) DS_TEST(NAME)
#endif*/

#ifndef TEST(NAME,NAME2) 
#define TEST(NAME,NAME2) DS_TEST(NAME2##NAME)
#endif



#ifndef PTEST(NAME)
#define PTEST(NAME) DS_TEST_PERFORMANCE(NAME)
#endif
  
#ifndef CHECK(condition)
#define CHECK(condition) DS_UNIT_TEST_CHECK(condition)
#endif

#ifndef CHECK_EQUAL(expected, actual)
#define CHECK_EQUAL(expected, actual) DS_UNIT_TEST_CHECK_EQUAL(expected, actual)
#endif
  
#ifndef LONGS_EQUAL(expected, actual)
#define LONGS_EQUAL(expected, actual) DS_UNIT_TEST_LONGS_EQUAL(expected, actual)
#endif

#ifndef DOUBLES_EQUAL(expected, actual,threshold)
#define DOUBLES_EQUAL(expected, actual,threshold) DS_UNIT_TEST_DOUBLES_EQUAL(expected, actual,threshold)
#endif