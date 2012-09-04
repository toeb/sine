#pragma once
#include <functional>
#include <algorithm>

#include <common/Config.h>

#include <common/Comparator.h>
#include <common/Query.h>
#include <common/ObservableCollection.h>


namespace nspace{

template<typename T>
class Set : public ObservableCollection<T>{   
public:
  //the underlying element vector
  std::vector<T> _elements;
 public:
 
   operator unsigned int() const {
     return size();
   }

  T first(){
    return at(0);
  }
  const T  first()const{
    return at(0);
  }
  T  at(unsigned int index){
    if(index >= size())return 0;
    return _elements[index];
  }
  const T at(unsigned  int index)const{
    if(index >= size())return 0;
    return _elements[index];
  }

  T operator()(unsigned int index){
    return at(index);
  }
  const T operator()(unsigned int index)const{
    return at(index);
  }
  
  template<typename CompareType>
  T operator()(CompareType val)const{
    return selectFirst([&val](T element){
      return compare(element,val);
    });
  }
  
  bool empty()const{
    return size()==0;
  }
  int size()const{
    return _elements.size();
  }
  const std::vector<T> & elements()const{return _elements;}
  
  void clear(){
    std::vector<T> elements = _elements;
    std::for_each(elements.begin(), elements.end(), [this](T element){
      this->remove(element);
    });
  }

  virtual bool add(T element){
    if(contains(element))return false;
    _elements.push_back(element);
    notifyElementAdded(element);
  }
  virtual bool remove(T element){
    bool result = Query<T>::remove(_elements,element);
    if(result)notifyElementRemoved(element);
    return result;
  }
  void copyFrom(const Set<T> & result){
    result.foreachElement([this](T t){
      this->add(t);
    });
  }
  void copyTo(Set<T> & result){
    foreachElement([&result](T t){
      result.add(t);
    });
  }
  void selectInto(Set<T> & result, std::function<bool (T) > f)const{
    Query<T>::select(result._elements,_elements,[f](bool & predicate, bool & cont, T elem){
      predicate = f(elem);
    });
  }
  bool contains(T  element)const{
    return selectFirst([element](T e){return e==element;})!=0;
  }
  

  Set<T> select(std::function<bool (T)> f)const{
    Set<T> result;
    selectInto(result,f);
    return result;
  }
  
  T selectFirst(std::function<bool (T)> f)const{
    return Query<T>::selectFirst(_elements,f);
  } 

  template<typename Result>
  void reduce(Result & result, std::function<void (Result & , T )> f)const{
    foreachElement([&result,f](T elem){
      f(result,elem);
    });
  }

  
  void foreachElement(std::function<void(T)> f)const{
    std::for_each(elements().begin(),elements().end(),f);
  }

  Set<T> & operator=(const Set<T>& a){
    if(&a==this)return*this;
    clear();
    copyFrom(a);
    return *this;
  }

  Set(const Set<T> & original){
    copyFrom(original);
  }

  Set(T element){
    add(element);
  }


  Set(){

  }

  ~Set(){
    clear();
  }


  //union
  Set<T> operator|(const Set<T> &b)const{
    return unite(*this,b);
  }

  
  
  //difference
  Set<T> operator/(const Set<T> & b)const{
    return difference(*this,b);
  }

  Set<T> & operator,(const Set<T> & b){    
    *this |= b;
    return *this;
  }

  Set<T> & operator |=(const Set<T> & b){
    b.reduce<Set<T> >(*this,[](Set<T> & accu,T element){
      accu.add(element);
    });
    return *this;
  }
  Set<T> & operator /=(const Set<T> & b){
    b.reduce<Set<T> >(*this,[](Set<T> & accu,T element){
      accu.remove(element);
    });
    return *this;
  }
  

  Set<T> operator ^(const Set<T> & b)const{
    return symetricDifference(*this, b);
  }
  Set<T> operator &(const Set<T> & b)const{
    return intersect(*this,b);
  }
  bool operator ==(const Set<T> & b)const{
    return areEqual(*this,b);
  }

  static bool areEqual(const Set<T> &a, const Set<T> & b){
    return symetricDifference(a,b).size()==0;
  }
  static Set<T> symetricDifference(const Set<T> &a , const Set<T> & b){
    return unite(difference(a,b),difference(b,a));
  }
  static Set<T> difference(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    result.copyFrom(a);
    b.reduce<Set<T> >(result,[](Set<T> & accu, T element){
      accu.remove(element);
    });
    return result;
  }
  static Set<T> unite(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    result.copyFrom(a);
    b.reduce<Set<T> >(result,[](Set<T>& accu, T element){
      if(!accu.contains(element))accu.add(element);
    });
    return result;
  }
  static Set<T> intersect(const Set<T> & a, const Set<T> & b){
    Set<T> result;
    b.reduce<Set<T> >(result,[&a](Set<T> & accu, T element){
      if(a.contains(element))accu.add(element);
    });
  }
  };

  
}
