#include <CppUnitLite/TestHarness.h>
#include <string>
#include <sstream>
#include <core.h>
#include <core.collection.h>
#include <vector>
using namespace nspace;
using namespace std;

using namespace nspace::collection;

#define ITEMTYPE(COLLECTIONTYPE) typename EnumerableItemType<COLLECTIONTYPE>::ItemType


template<typename T>
class Enumerator{
public:
  typedef T Item;
  // returns true if this enumerator is valid . ergo points to a valid item
  virtual operator bool()const=0;
  // returns a reference to the item
  virtual const Item& operator*()const=0;
  virtual Item& operator*()=0;
  // increments this enumerator
  virtual Enumerator<Item> & operator++()=0;

};
// enumerabletype need to have item() and size operation defined
// IndexType needs to have less than operator defined
template<typename IndexableType>
class IndexEnumerator : public Enumerator<ITEMTYPE(IndexableType) >{
  // Index type of indexable type
  typedef typename IndexableIndexType< IndexableType>::IndexType Index;
  IndexableType & _indexable;
  Index _index;
  //decalre friend so Indexabletype may instaciate IndexEnumerator
public:
  IndexEnumerator(IndexableType & indexable):_indexable(indexable),_index(0){}
  IndexEnumerator(IndexableType & indexable, const Index && index):_indexable(indexable),_index(index){}

  Enumerator<Item> & operator++(){
    _index++;
    return *this;
  }
  operator bool()const{
    auto n = size<Index>(_indexable);
    return _index < n;
  }
  const Item & operator*()const{
    return reference(_indexable, _index);
  }
  Item & operator*(){
    return reference(_indexable,_index);
  }
};



template<typename EnumerableType>
class EnumerableEnumeratorType{
public:
  typedef IndexEnumerator<EnumerableType> EnumeratorType;
};



template<typename EnumerableType>
class OperationGetEnumerator{
public:
  static inline typename EnumerableEnumeratorType<EnumerableType>::EnumeratorType  operation(EnumerableType & enumerable){
    return typename EnumerableEnumeratorType<EnumerableType>::EnumeratorType(enumerable);
  }
};





// creates the default enumerator for the EnumerableType
template<typename EnumerableType>
inline auto enumerator(EnumerableType & enumerable)->typename EnumerableEnumeratorType<EnumerableType>::EnumeratorType{
  return OperationGetEnumerator<EnumerableType>::operation(enumerable);
}

template<typename CollectionType>
class OperationCollectionAddItem{
public:
  static inline bool operation(CollectionType & collection, ITEMTYPE(CollectionType) item){
    return false;
  }

};
template<typename T>
class OperationCollectionAddItem<std::vector<T>>{
public:
  static inline bool operation(std::vector<T> & collection, T item){
    collection.push_back(item);
    return true;
  }

};

template<typename T>
class OperationCollectionAddItem<Set<T>>{
public:
  static inline bool operation(Set<T> & collection, T item){
    return collection.add(item);
  }

};


template<typename CollectionType>
bool addItem(CollectionType & collection, ITEMTYPE(CollectionType) item){
  return OperationCollectionAddItem<CollectionType>::operation(collection,item);
}


template<typename T>
class Concatenation{
public:

};
TEST(rvalue2, Tech){
  //Concatenation<int> con;
  //auto en=enumerator(con);
  int * aBefore =new int(3);


  auto f1 = []()->const int &{return int(3);};
  auto f2 =[&aBefore]()->const int &{return *aBefore;};

  const int & a = f1();
 const  int & b = f2();
  *aBefore = 5;
  cout <<aBefore<<endl;
  cout <<a<<endl;
  cout <<b<<endl;
}

TEST(rvalue1, Tech){
  int * aBefore =new int(3);


  auto f1 = []()->int&&{return std::move(int(3));};
  auto f2 =[&aBefore]()->int&&{return std::move(*aBefore);};

  auto a = f1();
  auto b = f2();
  *aBefore = 5;
  cout <<aBefore<<endl;
  cout <<a<<endl;
  cout <<b<<endl;
}

TEST(addItem1, Array){
  
  int arr[4] ={3,2,1,4};
  CHECK(!addItem(arr,5));
}
TEST(addItem1, stdvec){
  std::vector<int> vec;
  CHECK(addItem(vec,3));
  addItem(vec,3);
  addItem(vec,5);
  addItem(vec,2);

  CHECK(size(vec)==4);

}
TEST(addItem1, dsset){
  Set<int> vec;
  CHECK(addItem(vec,3));
  addItem(vec,3);
  addItem(vec,5);
  addItem(vec,2);
  // because  3 is only added once
  CHECK(size(vec)==3);

}


TEST(enumerator1,Array){
  int arr[4] ={3,2,1,4};
  IndexEnumerator<int[4]> enumerator(arr);
  CHECK(enumerator);
}
TEST(enumerator2,Array){
  int arr[4] ={3,2,1,4};
  IndexEnumerator<int[4]> enumerator(arr);
  CHECK(enumerator++);
}

TEST(enumerator3,Array){
  int arr[4] ={3,2,1,4};
  IndexEnumerator<int[4]> enumerator(arr);
  CHECK(enumerator++++);
}
TEST(enumerator4,Array){
  int arr[4] ={3,2,1,4};
  IndexEnumerator<int[4]> enumerator(arr);
  CHECK(enumerator++++++);
}
TEST(enumerator5,Array){
  int arr[4] ={3,2,1,4};
  IndexEnumerator<int[4]> enumerator(arr);
  CHECK(!enumerator++++++++);
}

TEST(enumerator6,Array){
  int arr[4] ={3,2,1,4};
  auto en = enumerator(arr);
  CHECK(!en++++++++);
}
TEST(enumerator1, stdvector){
  std::vector<int> vec;
  vec.push_back(3);
  vec.push_back(55);
  vec.push_back(22);
  vec.push_back(9);
  auto en = enumerator(vec);

  CHECK(en++++&&*en==22);
  
}
TEST(enumerator1, dslibSet){
  Set<int> s;
  s= 1,2,55,4;
  auto en = enumerator(s);
  
  //will not work because set<t> does not have pointer access to item
  CHECK(false);
 // CHECK(*en++++==55);

}



template<typename T>
class Union{
  
};
template<typename T>
class Difference{

};
template<typename T>
class Intersection{

};




class Collection{

};
class List{

};
//class Set

class EnumerableTraitsa{
  //traits
  static int itemType(){}
  typedef decltype(itemType()) Item;

  bool ordered;
  bool sorted;
  bool unique;
  bool null;
  
  void insertAfter(Item it){}
  void insertBefore(Item it){}
  void remove(Item it){}
  void swap(Item i1, Item i2){}
  void addFront(Item it){}
  void addBack(Item it){}
  void removeFirst(){}
  void removeLast(){}
  void replace(Item original, Item it){}


  void add(Item it){}

  void clear(){}


  // access
  void at(){}
  void reference(){}
  void copy(){}
  void pointer(){}

  //set theory
  void unite(){}
  void difference(){}
  void intersect(){}
  void symmetricDifference(){}
  void cartesionProduct(){}
  void powerSet(){}
  void zeroSet(){}

  // query
  void all(){}
  void any(){}
  void first(){}
  void last(){}
  void single(){}
  void subset(){}
  void aggregate(){}
  void iterate(){}
  void cast(){}
  void select(){}
  void foreach(){}
  
};





OPERATION(EnumerableIterator){
  OPERATION_IMPLEMENTATION(){
  
  }
};


TEST(LambdaDeclType, Tech){
  auto lambda = [](){return int(3);};
  decltype(lambda()) value;
  value =435;
}
TEST(LambdaMultilineReturnType, Tech){
  auto lambda = []()->double{
    int i=5; 
    return i*0.01;
  };
  decltype(lambda()) val;
  val = 2.1;
}


TEST(DataPointerAccess1, Collection){
  int arr[4]= {2,3,4,1};
  auto ptr= underlyingArray(arr);
  CHECK(arr==ptr);
};
TEST(DataPointerAccess2, Collection){
  std::list<int> arr;  
  arr.push_back(2);
  arr.push_back(3);
  auto ptr= underlyingArray(arr);
  CHECK(0==ptr);
};
TEST(DataPointerAccess3, Collection){
  std::vector<int> arr;
  arr.push_back(2);
  arr.push_back(3);
  
  auto ptr= underlyingArray(arr);
  CHECK(&arr[0]==ptr);
};


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
  CHECK(pointer(arr,2)==&arr[2]);
};
TEST(PointerAccess2, Collection){
  int arr[5]={1,2,123456,4,5};  
  int * arr2 = &*arr;
  CHECK(pointer(arr2,2)==&arr[2]);
};

TEST(Copy1,Collection){
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
