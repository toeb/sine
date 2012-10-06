#pragma once
#include <functional>
#include <algorithm>

#include <config.h>

#include <core/Comparator.h>
#include <core/Query.h>
#include <core/ObservableCollection.h>

namespace nspace{

  // a generic set (only unique elements allowed)
  template<typename T>
  class Set : public ObservableCollection<T>{   
  public:
    //the underlying element vector
    std::vector<T> _elements;
  public:
    // creates a copy from another set
    Set(const Set<T> & original);
    // creates a set from a single element
    Set(T element);
    //creates an empty set
    Set();
    // destroys the set
    ~Set();

    // removes all elements from the set
    void clear();
    // adds a element to the set
    virtual bool add(T element);
    // removes a element from the set
    virtual bool remove(T element);

    // returns cardinality  (size of the set)
    operator unsigned int() const;
    // returns true iff set is empty (size==0)
    bool empty()const;
    // returns the size of the set
    uint size()const;

    // returns last element
    T last();
    // returns last element
    const T last()const;
    // returns the first element
    T first();
    const T  first()const;
    // returns the element at index
    T  at(unsigned int index);
    const T at(unsigned  int index)const;
    // returns the element at index
    T operator()(unsigned int index);
    const T operator()(unsigned int index)const;
    // read access to the std::vector of elements 
    const std::vector<T> & elements()const;

    void sort(std::function<bool (const T, const T) > compare){
      std::sort(_elements.begin(),_elements.end(),compare);
    }

    // returns the first element matching the Compartype
    template<typename CompareType> T operator()(CompareType val)const;
    // returns the subset of elements where the predicate evaluates to true
    Set<T> subset(std::function<bool (T)> predicate)const;
    //returns the subset of elements which are of type T2
    template<typename T2>
    Set<T2> subset()const;

    // selects ResultType from this sets element
    template<typename ResultType> 
    Set<ResultType> select(std::function<ResultType (T)> selector)const;    
    // returns the first element were the predicate evaluates to true
    T first(std::function<bool (T)> f)const;
    // copies every element were the predicate evaluates to true to the result set
    void insertInto(Set<T> & result, std::function<bool (T) > predicate)const;
    // copies every element from other set to this set
    void copyFrom(const Set<T> & other);
    // copies every element from this set to the other set
    void copyTo(Set<T> & result);
    // returns true if the element is part of the set
    bool contains(T  element)const;



    // reduce into result
    template<typename Result> void reduce(Result & result, std::function<void (Result & , T )> f)const;
    // executes action on each element
    void foreachElement(std::function<void(T)> action)const;

    // assigns the elements of another set to this set discarding all current content
    Set<T> & operator=(const Set<T>& a);
    //union
    Set<T> operator|(const Set<T> &b)const;
    //difference
    Set<T> operator/(const Set<T> & b)const;
    // comma  extends the set by the elements of set b ( |= )
    Set<T> & operator,(const Set<T> & b);
    // exten set by elements of set b
    Set<T> & operator |=(const Set<T> & b);
    // removes all elements from set which are also contained in set b (difference equals)
    Set<T> & operator /=(const Set<T> & b);
    // returns the symmetric difference (xor)
    Set<T> operator ^(const Set<T> & b)const;
    // returns the intersection of this set and set b;
    Set<T> operator &(const Set<T> & b)const;
    // returns true if the sets contain exactly the same elements (symmetric difference has a cardinality of zero)
    bool operator ==(const Set<T> & b)const;

    //static are equal test
    static bool areEqual(const Set<T> &a, const Set<T> & b);
    // static symmetric difference 
    static Set<T> symmetricDifference(const Set<T> &a , const Set<T> & b);
    // static difference
    static Set<T> difference(const Set<T> & a, const Set<T> & b);
    // static union
    static Set<T> unite(const Set<T> & a, const Set<T> & b);
    // static intersection
    static Set<T> intersect(const Set<T> & a, const Set<T> & b);


  };

  //IMPLEMENTATION FOLLOWS:
  // returns last element
  template<typename T>
  T  Set<T>::last(){return at(size()-1);}
  // returns last element
  template<typename T>
  const T  Set<T>::last()const{return at(size()-1);}

  template<typename T>
  template<typename T2>
  Set<T2> Set<T>::subset()const{
    return subset([](T t){return dynamic_cast<T2>(t)!=0;}).select([](T t){return dynamic_cast<T2>(t);});
  }

  template<typename T>
  template<typename ResultType> 
  Set<ResultType> Set<T>::select(std::function<ResultType (T)> selector)const{
    Set<ResultType> result;
    foreachElement([&result, selector](T element){
      result |= selector(element);
    });
    return result;
  }

  // returns cardinality  (size of the set)
  template<typename T>
  Set<T>::operator unsigned int() const {
    return size();
  }

  // returns the first element
  template<typename T>
  T Set<T>::first(){
    return at(0);
  }

  template<typename T>
  const T  Set<T>::first()const{
    return at(0);
  }
  template<typename T>
  T  Set<T>::at(unsigned int index){
    if(index >= size())return 0;
    return _elements[index];
  }
  template<typename T>
  const T Set<T>::at(unsigned  int index)const{
    if(index >= size())return 0;
    return _elements[index];
  }
  template<typename T>
  T Set<T>::operator()(unsigned int index){
    return at(index);
  }
  template<typename T>
  const T Set<T>::operator()(unsigned int index)const{
    return at(index);
  }

  template<typename T>
  template<typename CompareType>
  T Set<T>::operator()(CompareType val)const{
    return first([&val](T element){
      return compare(element,val);
    });
  }


  template<typename T>
  bool Set<T>::empty()const{
    return size()==0;
  }
  template<typename T>
  uint Set<T>::size()const{
    return _elements.size();
  }
  template<typename T>
  const std::vector<T> & Set<T>::elements()const{return _elements;}
  template<typename T>
  void Set<T>::clear(){
    std::vector<T> elements = _elements;
    std::for_each(elements.begin(), elements.end(), [this](T element){
      this->remove(element);
    });
  }
  template<typename T>
  bool Set<T>::add(T element){
    if(contains(element))return false;
    _elements.push_back(element);
    notifyElementAdded(element);
    return true;
  }
  template<typename T>
  bool Set<T>::remove(T element){
    bool result = Query<T>::remove(_elements,element);
    if(result)notifyElementRemoved(element);
    return result;
  }
  template<typename T>
  void Set<T>::copyFrom(const Set<T> & result){
    result.foreachElement([this](T t){
      this->add(t);
    });
  }
  template<typename T>
  void Set<T>::copyTo(Set<T> & result){
    foreachElement([&result](T t){
      result.add(t);
    });
  }
  template<typename T>
  void Set<T>::insertInto(Set<T> & result, std::function<bool (T) > f)const{
    Query<T>::select(result._elements,_elements,[f](bool & predicate, bool & cont, T elem){
      predicate = f(elem);
    });
  }
  template<typename T>
  bool Set<T>::contains(T  element)const{
    return first([element](T e){return e==element;})!=0;
  }

  template<typename T>
  Set<T> Set<T>::subset(std::function<bool (T)> f)const{
    Set<T> result;
    insertInto(result,f);
    return result;
  }



  template<typename T>
  T Set<T>::first(std::function<bool (T)> f)const{
    return Query<T>::selectFirst(_elements,f);
  } 

  template<typename T>
  template<typename Result>
  void Set<T>::reduce(Result & result, std::function<void (Result & , T )> f)const{
    foreachElement([&result,f](T elem){
      f(result,elem);
    });
  }

  template<typename T>
  void Set<T>::foreachElement(std::function<void(T)> f)const{
    for(uint i=0; i < _elements.size();i++){
      f(_elements[i]);
    }
  }
  template<typename T>
  Set<T> & Set<T>::operator=(const Set<T>& a){
    if(&a==this)return*this;
    clear();
    copyFrom(a);
    return *this;
  }
  template<typename T>
  Set<T>::Set(const Set<T> & original){
    copyFrom(original);
  }
  template<typename T>
  Set<T>::Set(T element){
    add(element);
  }

  template<typename T>
  Set<T>::Set(){

  }
  template<typename T>
  Set<T>::~Set(){
    clear();
  }


  //union
  template<typename T>
  Set<T> Set<T>::operator|(const Set<T> &b)const{
    return unite(*this,b);
  }



  //difference
  template<typename T>
  Set<T> Set<T>::operator/(const Set<T> & b)const{
    return difference(*this,b);
  }
  template<typename T>
  Set<T> & Set<T>::operator,(const Set<T> & b){    
    *this |= b;
    return *this;
  }
  template<typename T>
  Set<T> & Set<T>::operator |=(const Set<T> & b){
    b.reduce<Set<T> >(*this,[](Set<T> & accu,T element){
      accu.add(element);
    });
    return *this;
  }
  template<typename T>
  Set<T> & Set<T>::operator /=(const Set<T> & b){

    b.reduce<Set<T> >(*this,[](Set<T> & accu,T element){
      accu.remove(element);
    });
    return *this;
  }

  template<typename T>
  Set<T> Set<T>::operator ^(const Set<T> & b)const{
    return symetricDifference(*this, b);
  }
  template<typename T>
  Set<T> Set<T>::operator &(const Set<T> & b)const{
    return intersect(*this,b);
  }
  template<typename T>
  bool Set<T>::operator ==(const Set<T> & b)const{
    return areEqual(*this,b);
  }
  template<typename T>
  bool Set<T>::areEqual(const Set<T> &a, const Set<T> & b){
    return symetricDifference(a,b).size()==0;
  }
  template<typename T>
  Set<T> Set<T>::symmetricDifference(const Set<T> &a , const Set<T> & b){
    return unite(difference(a,b),difference(b,a));
  }
  template<typename T>
  Set<T> Set<T>::difference(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    result.copyFrom(a);
    b.reduce<Set<T> >(result,[](Set<T> & accu, T element){
      accu.remove(element);
    });
    return result;
  }
  template<typename T>
  Set<T> Set<T>::unite(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    result.copyFrom(a);
    b.reduce<Set<T> >(result,[](Set<T>& accu, T element){
      if(!accu.contains(element))accu.add(element);
    });
    return result;
  }
  template<typename T>
  Set<T> Set<T>::intersect(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    b.reduce<Set<T> >(result,[&a](Set<T> & accu, T element){
      if(a.contains(element))accu.add(element);
    });
  }

}
