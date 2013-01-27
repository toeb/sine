#include <core.testing.h>
#include <string>
#include <sstream>
#include <core.h>
#include <core.collection.h>
#include <vector>
#include <core/collection/Enumerable.h>
using namespace nspace;
using namespace std;

using namespace nspace::collection;





// enumerabletype need to have item() and size operation defined
// IndexType needs to have less than operator defined
template<typename IndexableType>
class IndexEnumeratorImplementation : public EnumeratorImplementation<ITEMTYPE(IndexableType) >{
  // Index type of indexable type
  typedef typename IndexableIndexType< IndexableType>::IndexType Index;
  IndexableType & _indexable;
  Index _index;
public:
  //decalre friend so Indexabletype may instaciate IndexEnumerator
  IndexEnumeratorImplementation(IndexableType & indexable):_indexable(indexable),_index(0){}
  IndexEnumeratorImplementation(IndexableType & indexable, const Index & index):_indexable(indexable),_index(index){}
  
protected:
  void moveNext(){
    _index++;
  }
  std::shared_ptr<EnumeratorImplementation<ITEMTYPE(IndexableType)> >clone(){
    return std::shared_ptr<IndexEnumeratorImplementation<IndexableType>>(new IndexEnumeratorImplementation(_indexable, _index));
  }
  bool isValid()const{
    auto n = size<Index>(_indexable);
    return _index < n;
  }
  const ITEMTYPE(IndexableType) & currentItem()const{
    return reference(_indexable, _index);
  }
  ITEMTYPE(IndexableType) & currentItem(){
    return reference(_indexable,_index);
  }
};



template<typename EnumerableType>
class EnumerableEnumeratorType{
public:
  typedef IndexEnumeratorImplementation<EnumerableType> EnumeratorType;
};



template<typename EnumerableType>
class OperationGetEnumerator{
public:
  static inline typename EnumerableEnumeratorType<EnumerableType>::EnumeratorType  operation(EnumerableType & enumerable){
    return typename EnumerableEnumeratorType<EnumerableType>::EnumeratorType(enumerable);
  }
};
template<typename EnumerableType>
class OperationGetEnumeratorImplementation{
public:
  typedef ITEMTYPE(EnumerableType) Item;
  static inline auto operation(EnumerableType  & enumerable)-> EnumeratorImplementation<Item> *{
    return new IndexEnumeratorImplementation<EnumerableType>(enumerable);
  }
};


template<typename T>
class OperationGetEnumeratorImplementation<SimpleLinkedList<T> >{
public:
  typedef T Item;
  static inline auto operation(SimpleLinkedList<T>  & enumerable)-> EnumeratorImplementation<Item> *{
    return new SimpleLinkedListEnumerator<T>(enumerable);
  }
};


template<typename EnumerableType>
class EnumerableImplementationWrapper : public EnumerableImplementation<ITEMTYPE(EnumerableType)>{
private:
  EnumerableType & _enumerable;
public:
  typedef ITEMTYPE(EnumerableType) Item;
  EnumerableImplementationWrapper(EnumerableType & enumerable):_enumerable(enumerable){
    
  }
  
  virtual Enumerator<Item> getEnumerator(){
    //  typedef std::remove_pointer<typename decltype(OperationGetEnumeratorImplementation<EnumerableType>::operation(_enumerable))>::type EnumeratorType;
    return Enumerator<Item>(std::shared_ptr<EnumeratorImplementation<Item> > (OperationGetEnumeratorImplementation<EnumerableType>::operation(_enumerable)));
  }

};

template<typename EnumerableType>
class OperationGetEnumerableImplementation{
public:
  typedef ITEMTYPE(EnumerableType) Item;
  static EnumerableImplementation<Item>* operation(EnumerableType & enumerable){
    return new EnumerableImplementationWrapper<EnumerableType>(enumerable);
  }
};


template<typename EnumerableType>
auto enumerable(EnumerableType & items)->Enumerable<ITEMTYPE(EnumerableType)>{
    return Enumerable<ITEMTYPE(EnumerableType)>(OperationGetEnumerableImplementation<EnumerableType>::operation(items));
}
// creates the default enumerator for the EnumerableType
template<typename EnumerableType>
inline auto enumerator(EnumerableType & items)->Enumerator<ITEMTYPE(EnumerableType)>{
  return enumerable(items).getEnumerator();
}

template<typename CollectionType>
class OperationCollectionAddItem{
public:
  static inline bool operation(CollectionType & collection, const ITEMTYPE(CollectionType) & item){
    return false;
  }

};
template<typename T>
class OperationCollectionAddItem<std::vector<T> >{
public:
  static inline bool operation(std::vector<T> & collection,const T &item){
    collection.push_back(item);
    return true;
  }

};

template<typename T>
class OperationCollectionAddItem<Set<T> >{
public:
  static inline bool operation(Set<T> & collection,const T & item){
    return collection.add(item);
  }

};
template<typename T>
class OperationCollectionAddItem<SimpleLinkedList<T> >{
public:
  static inline bool operation(SimpleLinkedList<T> & collection,const T &item){
    collection.add(item);
    return true;
  }

};


template<typename CollectionType>
bool addItem(CollectionType & collection, const ITEMTYPE(CollectionType) & item){
  return OperationCollectionAddItem<CollectionType>::operation(collection,item);
}



/*
template<typename T>
class OperationGetEnumerableImplementation<std::vector<T>>{
public:
  static EnumerableImplementation<T>* operation(std::vector<T> & enumerable){
    return 0;
  }
};

template<typename T>
class OperationGetEnumerableImplementation<T*>{
public:
  static EnumerableImplementation<T> *operation(T* enumerable){
    return 0;
  }
};
template<typename T, size_t n> 
class OperationGetEnumerableImplementation<T[n]>{
public:
  static EnumerableImplementation<T>* operation(T (&enumerable)[n]){
    return new EnumerableImplementationWrapper<T[n]>(enumerable);
  }
};
*/



/*
template<typename T>
class Concatenation{
  std::vector<Enumerable<T>*> _enumerators;
public:
  class ConcatEnumerator : public Enumerator<T>{
    Concatenation<T> & _concatenation;
  public:

  };
  ConcatEnumerator getEnumerator(){
    return ConcatEnumerator(*this);
  }
};

TEST(add1,SimpleLinkedList){
  SimpleLinkedList<std::string> list;
  addItem(list,"hello");
}
TEST(enumerable1, SimpleLinkedList){
  
  SimpleLinkedList<std::string> list;
  addItem(list,"hello");
  addItem(list,"world");
  auto w = enumerator(list);
  stringstream ss;
  while(w){
    ss<<*w;
    w++;
  }
  CHECK(ss.str()=="helloworld");
}

TEST(enumerable1,arr){
  int arr[4]={1,3,4,2};
  auto w = enumerable(arr);
  auto enumerat=w.getEnumerator();
  CHECK(enumerat);
}
TEST(enumerable1, stdvec){
  std::vector<string> vec;
  addItem(vec,"hello");
  addItem(vec,"world");

  auto w = enumerable(vec);
  auto x = w.getEnumerator();
  CHECK(x);
  stringstream ss;
  while(x){
    ss << *x;
    x++;
  }
  CHECK(ss.str()=="helloworld");
}


TEST(enumerable2,arr){
  int arr[4]={1,3,4,2};
  auto w = enumerable(arr);
  auto enumerat=w.getEnumerator();
  stringstream ss;
  while(enumerat){
    ss << *enumerat;
    enumerat++;
  }
  CHECK(ss.str()=="1342");
}



*/


TEST(rvalue2, Tech){
  //Concatenation<int> con;
  //auto en=enumerator(con);
  int * aBefore =new int(3);


  auto f1 = []()->const int &{return int(3);};
  auto f2 = [&aBefore]()->const int &{return *aBefore;};

  const int & a = f1();
  const int & b = f2();
  *aBefore = 5;

}

TEST(rvalue1, Tech){
  int * aBefore =new int(3);


  auto f1 = []()->int&&{return std::move(int(3));};
  auto f2 =[&aBefore]()->int&&{return std::move(*aBefore);};

  auto a = f1();
  auto b = f2();
  *aBefore = 5;

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
  Enumerator<int> enumerator(shared_ptr<IndexEnumeratorImplementation<int[4]>>(new IndexEnumeratorImplementation<int[4]>(arr)));
  CHECK(enumerator);
}
/*
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
*/


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
  auto result = std::is_same<decltype(lambda()),double>::value;
  CHECK(result);
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

  size_t n;
  auto success = size(n,arrayPointer);
  CHECK(success==false);
};
TEST(Size4, Collection){
  Set<int> set;
  set =1,4,5,6,34,3,2;

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
