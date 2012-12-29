#pragma once
#include <config.h>

#include <core.collection.h>
#include <core/collection/operations/OperationCollectionItemType.h>
#include <core/collection/operations/OperationCollectionItemAccess.h>
#include <memory>
// is replaced by the item type that the ENUMERABLETYPE contains
#define ITEMTYPE(ENUMERABLETYPE) typename EnumerableItemType<ENUMERABLETYPE>::ItemType

namespace nspace{
  namespace collection{
    // forwad declarations
    template<typename T>
    class Enumerator;
    template<typename T>
    class Enumerable;
    template<typename T>

    // enumerator implementation
    class EnumeratorImplementation{
    protected:
      typedef T Item;
      virtual bool isValid()const=0;
      virtual T&currentItem()=0;
      virtual const T & currentItem()const=0;
      virtual void moveNext()=0;
      virtual std::shared_ptr<EnumeratorImplementation<T>> clone()=0;
      friend class Enumerator<T>;
    };

    // enumerator class wraps an enumerator implementation
    template<typename T>
    class Enumerator{
    public:
      Enumerator(std::shared_ptr<EnumeratorImplementation<T>> impl):_implementation(impl){}
      Enumerator(Enumerator<T> & other):_implementation(other._implementation){}
      // returns true if this enumerator is valid . ergo points to a valid item
      operator bool()const{return _implementation->isValid();};
      // returns a reference to the item
      const T& operator*()const{return _implementation->currentItem();}
      T& operator*(){return _implementation->currentItem(); }
      // increments this enumerator
      Enumerator<T> operator++(int){
        Enumerator<T> result = Enumerator<T>(_implementation->clone()) ;
        _implementation->moveNext();
        return result;
      }
      Enumerator<T> & operator++(){
        _implementation->moveNext();
        return * this;
      }
    private:
      std::shared_ptr<EnumeratorImplementation<T>> _implementation;
    };

    template<typename T>
    class EnumerableImplementation{
    protected:
      virtual Enumerator<T> getEnumerator()=0;
      friend class Enumerable<T>;
    };

    template<typename T>
    class Enumerable{
    public:
      Enumerable(EnumerableImplementation<T>* implemenation):_implementation(implemenation){}
      Enumerator<T> getEnumerator(){return _implementation->getEnumerator();};
    private:
      std::shared_ptr<EnumerableImplementation<T>> _implementation;
    };
  }
}
