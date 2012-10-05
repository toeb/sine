#pragma once

#include <core/Set.h>
#include <core/Comparator.h>

namespace nspace{


  template<typename Derived>
  class Node : public ObservableCollection<Derived*>, public ObservableCollection<Derived*>::Observer{
  private:
    Set<Derived*> _predecessors;
    Set<Derived*> _successors;
    Derived & _this;
  public:    
    // returns a reference to this node but already cast to its derived type
    inline Derived & derived();
    // same as above w/o write access
    inline const Derived & derived()const;
    Node();
    ~Node();
    // callback when an element is added to the node. makes sure that the nodes are connected in both directions
    void elementAdded(ObservableCollection<Derived*> * sender, Derived * node);
    // callback when an element is removed from the node. makes sure the nodes are removed
    void elementRemoved(ObservableCollection<Derived*> * sender, Derived * node);
    // all connected nodes (union of predecessors and successors)
    Set<Derived*> neighbors()const;
    // read access to predecessors
    const Set<Derived*> & predecessors()const;
    // read write access to predecessors
    Set<Derived*> & predecessors();
    // read write access to successor by index
    Derived * successor(uint i);
    // read access to successor by index
    const Derived * successor(uint i)const;
    //read / write access to predecessor by index
    Derived * predecessor(uint i);
    // read access to predecessor by index
    const Derived * predecessor(uint i)const;
    // read access tot first successor
    const Derived * firstSuccessor()const;
    //read write access to first successor
    Derived * firstSuccessor();
    // returns the first predecessor (const)
    const Derived * firstPredecessor()const;
    // returns the first predecessor
    Derived * firstPredecessor();
    // allows const access to the successors
    const Set<Derived*> & successors()const;
    //allows access to the successors
    Set<Derived*> & successors();
    // adds a set of predecessors (arrows indicate direction of connection
    Derived & operator <<(const Set<Derived*> & nodes);
    // adds a set of successors 
    Derived & operator >>(const Set<Derived*> & nodes);
    // adds a single predecessor
    Derived & operator <<(Derived & node);
    //adds a single successor
    Derived & operator >>(Derived & node);
    // adds a single predecessor (by pointer)
    Derived & operator <<(Derived * node);
    // adds a single successor (by pointer)
    Derived & operator >>(Derived * node);
    // iterates the neigbors
    void foreachNeighbor(std::function<void (Derived*)> action)const;
    // iterates the predecessors
    void foreachPredecessor(std::function<void (Derived*)> action)const;
    // iterates the successors
    void foreachSuccessor(std::function<void (Derived*)> action)const;

    void dfs(std::function<void (Derived * )> action);
    // really bad implementation of dfs, it is slow and will crash (stack overflow ) if there are cycles in the graph
    void dfs(std::function<void (bool & , Derived *)> f, std::function<void (Set<Derived*> &, const Derived &) > successors);
    // also a realy bad implemention. this time of bfs (performancewise). it does not crash if cycles are contained and returns the number of cycles found
    int bfs(std::function<void (bool& ,Derived*)> f,std::function<void (Set<Derived*> &, const Derived &) > successors);
    // overload
    int bfs(std::function<void (bool& ,Derived*)> f);

    virtual void onPredecessorAdded(Derived * predecessor){}
    virtual void onSuccessorAdded(Derived * successor){}
    virtual void onPredecessorRemoved(Derived* predecessor){}
    virtual void onSuccessorRemoved(Derived * predecessor){}

  };


  // implementation of node

  template<typename Derived>
  void Node<Derived>::foreachNeighbor(std::function<void (Derived*)> action)const{
    neighbors().foreachElement(action);
  }
  template<typename Derived>
  void Node<Derived>::foreachPredecessor(std::function<void (Derived*)> action)const{
    predecessors().foreachElement(action);
  }
  template<typename Derived>
  void Node<Derived>::foreachSuccessor(std::function<void (Derived*)> action)const{
    successors().foreachElement(action);
  }

  template<typename Derived>
  inline Derived & Node<Derived>::derived(){return _this;}
  template<typename Derived>
  inline const Derived & Node<Derived>::derived()const{return _this;}
  template<typename Derived>
  Node<Derived>::Node():_this(*static_cast<Derived*>(this)){
    _predecessors.addObserver(this);
    _successors.addObserver(this);

  }
  template<typename Derived>
  Node<Derived>::~Node(){
    _predecessors.clear();
    _successors.clear();
  }
  // callback when an element is added to the node. makes sure that the nodes are connected in both directions
  template<typename Derived>
  void Node<Derived>::elementAdded(ObservableCollection<Derived*> * sender, Derived * node){
    if(sender==&_predecessors) {        
      onPredecessorAdded(node);
      node->successors() |= &derived();
    }
    if(sender==&_successors) {
      onSuccessorAdded(node);
      node->predecessors()|=&derived();
    }
  }
  // callback when an element is removed from the node. makes sure the nodes are removed
  template<typename Derived>
  void Node<Derived>::elementRemoved(ObservableCollection<Derived*> * sender, Derived * node){
    if(sender==&_predecessors) {
      onPredecessorRemoved(node);
      node->successors() /=&derived();
    }
    if(sender==&_successors){
      onSuccessorRemoved(node);
      node->predecessors()/=&derived();
    }
  }
  // all connected nodes (union of predecessors and successors)
  template<typename Derived>
  Set<Derived*> Node<Derived>::neighbors()const{
    return predecessors()|successors();
  }
  // read access to predecessors
  template<typename Derived>
  const Set<Derived*> & Node<Derived>::predecessors()const{return _predecessors;}
  // read write access to predecessors
  template<typename Derived>
  Set<Derived*> & Node<Derived>::predecessors(){return _predecessors;}
  // read write access to successor by index
  template<typename Derived>
  Derived * Node<Derived>::successor(uint i){return successors().at(i);}
  // read access to successor by index
  template<typename Derived>
  const Derived * Node<Derived>::successor(uint i)const{return successors().at(i);}
  //read / write access to predecessor by index
  template<typename Derived>
  Derived * Node<Derived>::predecessor(uint i){return predecessors().at(i);}
  // read access to predecessor by index
  template<typename Derived>
  const Derived * Node<Derived>::predecessor(uint i)const{return predecssors().at(i);}
  // read access tot first successor
  template<typename Derived>
  const Derived * Node<Derived>::firstSuccessor()const{return successors().first();}
  //read write access to first successor
  template<typename Derived>
  Derived * Node<Derived>::firstSuccessor(){return successors().first();}
  // returns the first predecessor (const)
  template<typename Derived>
  const Derived * Node<Derived>::firstPredecessor()const{return predecessors().first();}    
  // returns the first predecessor
  template<typename Derived>
  Derived * Node<Derived>::firstPredecessor(){return predecessors().first();}
  // allows const access to the successors
  template<typename Derived>
  const Set<Derived*> & Node<Derived>::successors()const{return _successors;}
  //allows access to the successors
  template<typename Derived>
  Set<Derived*> & Node<Derived>::successors(){return _successors;}


  // adds a set of predecessors (arrows indicate direction of connection
  template<typename Derived>
  Derived & Node<Derived>::operator <<(const Set<Derived*> & nodes){
    predecessors() |= nodes;
    return derived();
  }
  // adds a set of successors 
  template<typename Derived>
  Derived & Node<Derived>::operator >>(const Set<Derived*> & nodes){
    successors() |= nodes;
    return derived();
  }
  // adds a single predecessor
  template<typename Derived>
  Derived & Node<Derived>::operator <<(Derived & node){
    predecessors().add(&node);
    return derived();
  }
  //adds a single successor
  template<typename Derived>
  Derived & Node<Derived>::operator >>(Derived & node){
    successors().add(&node);
    return derived();
  }
  // adds a single predecessor (by pointer)
  template<typename Derived>
  Derived & Node<Derived>::operator <<(Derived * node){
    predecessors().add(node);
    return derived();
  }
  // adds a single successor (by pointer)
  template<typename Derived>
  Derived & Node<Derived>::operator >>(Derived * node){
    successors().add(node);
    return derived();
  }


  template<typename Derived>
  void Node<Derived>::dfs(std::function<void (Derived * )> action){
    auto a = [action](bool& b, Derived * d){action(d);};
    auto b = [](Set<Derived * > & successors, const Derived & current){successors |= current.successors();};
    dfs(a,b );
  }

  // really bad implementation of dfs, it is slow and will crash (stack overflow ) if there are cycles in the graph
  template<typename Derived>
  void Node<Derived>::dfs(std::function<void (bool & , Derived *)> f, std::function<void (Set<Derived*> &, const Derived &) > successors){
    Set<Derived* > next;
    successors(next,derived());
    bool cont=true;
    f(cont,&derived());
    if(!cont)return;
    next.foreachElement([f,successors](Derived * n){
      n->dfs(f,successors);
    });      
  }

  // also a realy bad implemention. this time of bfs (performancewise). it does not crash if cycles are contained and returns the number of cycles found
  template<typename Derived>
  int Node<Derived>::bfs(std::function<void (bool& ,Derived*)> f,std::function<void (Set<Derived*> &, const Derived &) > successors){
    Set<Derived *> list = &derived();
    int cycles =0;
    while(list){
      // get first element
      Derived * current = list.first();
      // remove first element
      list /= current;

      //execute function
      bool cont = true;
      f(cont,current);
      if(!cont)return cycles;

      // add successors of current;
      successors(list,*current);
    }
    return cycles;
  }


  // overload
  template<typename Derived>
  int Node<Derived>::bfs(std::function<void (bool& ,Derived*)> f){
    std::function<void (Set<Derived*> &, const Derived &) > sfunc = [](Set<Node *>& successors,const Derived & node){        successors |= node.successors();      };
    return bfs(f,sfunc);
  }



}