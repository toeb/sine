#pragma once
#include <core/Query.h>

namespace nspace{

/**
 * \brief A collection that will notify its observers if elements were added or removed
 */
template<typename T> class ObservableCollection{
public:
  /**
   * \brief Observer class.
   */
  class Observer{
  public:
    virtual void collectionChanged(ObservableCollection<T> * sender){}
    virtual void elementAdded(ObservableCollection<T> * sender, T element){}
    virtual void elementRemoved(ObservableCollection<T> * sender, T element){}
  };
  class DelegateElementAddedObserver:Observer{
    std::function<void (ObservableCollection<T> ,T) > _callback;
    DelegateElementAddedObserver(std::function<void (ObservableCollection<T> ,T) > callback):_callback(callback){}
    virtual void elementAdded(ObservableCollection<T> * sender, T element){_callback(sender,element);}
  };
  class DelegateElementRemovedObserver:Observer{
    std::function<void (ObservableCollection<T> ,T) > _callback;
    DelegateElementRemovedObserver(std::function<void (ObservableCollection<T> ,T) > callback):_callback(callback){}
    virtual void elementRemoved(ObservableCollection<T> * sender, T element){_callback(sender,element);}
  };
private:  
  std::vector<Observer*> _observers;
protected:

  /**
   * \brief gets called when an element is added
   * 				subclasses may implement this
   *
   * \param element The element.
   */
  virtual void onElementAdded(T element){}

  /**
   * \brief called when an element is removed
   * 				subclasses may implement this
   *
   * \param element The element.
   */
  virtual void onElementRemoved(T element){}  

  /**
   * \brief Notifies observers that an element was added.
   * 				subclasses should call this
   *
   * \param element The element.
   */
  void notifyElementAdded(T element){
    onElementAdded(element);    
    Query<Observer* >::foreachElement(_observers,[this,&element](Observer * observer){
      observer->elementAdded(this,element);
    });
  }

  /**
   * \brief Notifies observers that an element was removed.
   * 				subclasses should call this
   *      
   * \param element The element.
   */
  void notifyElementRemoved(T element){
    onElementRemoved(element);
    Query<Observer* >::foreachElement(_observers, [this,&element](Observer * observer){
       observer->elementRemoved(this,element);
    });
  }
public:

  /**
   * \brief Adds an observer which is notified when collection is changed
   *
   * \param [in]  observer  If non-null, the observer.
   */
  void addObserver(Observer * observer){
    _observers.push_back(observer);
  }

  /**
   * \brief Removes the observer described by observer.
   *
   * \param [in]  observer  the observer.
   */
  void removeObserver(Observer * observer){
    Query<Observer*>::remove(_observers,observer);
  }
};
}
