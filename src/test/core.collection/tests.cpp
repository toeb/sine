#include <CppUnitLite/TestHarness.h>
#include <string>
#include <sstream>
#include <core.h>
#include <core.collection.h>
#include <vector>
using namespace nspace;
using namespace std;

using namespace nspace::collection;

TEST(Size1, Collection){
  int someArray[5];
  CHECK(size(someArray)==5);
};


TEST(Size2, Collection){
  std::vector<int> vec;
  vec.push_back(4);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(2);
  vec.push_back(1);
  CHECK(size(vec)==5);
};
TEST(Size3, Collection){
  int * arrayPointer = new int[5];
  // cannot form any conclusion about s - it is undefined
  auto s= size(arrayPointer);
  size_t n;
  auto success = size(n,arrayPointer);
  CHECK(success==false);
};
TEST(Size4, Collection){
  Set<int> set;
  set =1,4,5,6,34,3,2;
  auto result = size(set);
  CHECK(size(set)==7);
};
TEST(Size5, Collection){
  std::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  CHECK(size(lst)==3);
};

TEST(ItemAccess1, Collection){
  int arr[5]={1,2,123456,4,5};
  CHECK(item<int>(arr,2)==123456);
};
TEST(ItemAccess2, Collection){
  int arr[5]={1,2,123456,4,5};
  int * arr2 = &*arr;
  CHECK(item<int>(arr2,2)==123456);
};
TEST(ItemAccess3, Collection){
  Set<int> set;
  set =1,2,123456,4,5;
  CHECK(item<int>(set,2)==123456);
};
TEST(ItemAccess4, Collection){
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(232323);
  vec.push_back(4);
  CHECK(item<int>(vec,2)==232323);
};

TEST(PointerAccess1, Collection){
  int arr[5]={1,2,123456,4,5};  
  CHECK(pointer<int>(arr,2)==&arr[2]);
};
TEST(PointerAccess2, Collection){
  int arr[5]={1,2,123456,4,5};  
  int * arr2 = &*arr;
  CHECK(pointer<int>(arr2,2)==&arr[2]);
};

TEST(Copy1){
  Set<int> source;
  source = 7,1,2,3,4,5;
  int arr[6];
  CHECK(copy(arr,source));
  CHECK(arr[0]==7);
  CHECK(arr[1]==1);
  CHECK(arr[2]==2);
  CHECK(arr[3]==3);
  CHECK(arr[4]==4);
  CHECK(arr[5]==5);

};
/*
TEST(CopyRange1, Collection){
  int arr[5]={1,3123123,123456,4,5};  
  int arr[6]={1,2,3,4,5,6};
  


  int * arr2 = &*arr;
  CHECK(pointer<int>(arr2,2)==&arr[2]);
};
*/