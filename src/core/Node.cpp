#include "Node.h"
using namespace nspace;
using namespace std;


void Comparator<Node*,const char*>::operation(bool & result, const Node * a, const char * c){
  result = *a==string(c);
}


 Node::Node(){
      _predecessors.addObserver(this);
      _successors.addObserver(this);
    }
    // creates  named node
    Node::Node(const std::string & name){
      setName(name);
      _predecessors.addObserver(this);
      _successors.addObserver(this);
    }

    // destroys node. causing all connected nodes to be disconnected
    Node::~Node(){_predecessors.clear(); _successors.clear();}

    // all connected nodes (union of predecessors and successors)
    Set<Node*> Node::neighbors()const{return predecessors()|successors();};


    const Set<Node*> & Node::predecessors()const{
      return _predecessors;
    }

    Set<Node*> & Node::predecessors(){
      return _predecessors;
    }

    Node * Node::successor(uint i){
      return _successors.at(i);
    }
    const Node * Node::successor(uint i)const{
      return _successors.at(i);
    }

    Node * Node::predecessor(uint i){
      return _successors.at(i);
    }
    const Node * Node::predecessor(uint i)const{
      return _successors.at(i);
    }

    const Node * Node::firstSuccessor()const{
      return successor(0);
    }
    Node * Node::firstSuccessor(){
      return successor(0);
    }

    const Node * Node::firstPredecessor()const{
      return predecessor(0);
    }

    Node * Node::firstPredecessor(){
      return predecessor(0);
    }



    const Set<Node*> & Node::successors()const{
      return _successors;
    }

    Set<Node*> & Node::successors(){
      return _successors;
    }

    // adds a set of predecessors (arrows indicate direction of connection
    Node & Node::operator <<(const Set<Node*> & nodes){
      predecessors() |= nodes;
      return *this;
    }
    // adds a set of successors 
    Node & Node::operator >>(const Set<Node*> & nodes){
      successors() |= nodes;
      return *this;
    }
    // adds a single predecessor
    Node & Node::operator <<(Node & node){
      predecessors().add(&node);
      return *this;
    }
    //adds a single successor
    Node & Node::operator >>(Node & node){
      successors().add(&node);
      return *this;
    }
    // adds a single predecessor (by pointer)
    Node & Node::operator <<(Node * node){
      predecessors().add(node);
      return *this;
    }
    // adds a single successor (by pointer)
    Node & Node::operator >>(Node * node){
      successors().add(node);
      return *this;
    }
    // overload for dfs(f,successors)
    void Node::dfs(std::function<void (bool & , Node *)> f){
      dfs(f,[](Set<Node *>& successors,const Node & node){ successors |= node.successors(); });
    }
    // really bad implementation of dfs, it is slow and will crash (stack overflow ) if there are cycles in the graph
    void Node::dfs(std::function<void (bool & , Node *)> f, std::function<void (Set<Node*> &, const Node &) > successors){

      Set<Node* > next;
      successors(next,*this);
      bool cont=true;
      f(cont,this);
      if(!cont)return;
      next.foreachElement([f,successors](Node * n){
        n->dfs(f,successors);
      });      
    }

    // also a realy bad implemention. this time of bfs (performancewise). it does not crash if cycles are contained and returns the number of cycles found
    int Node::bfs(std::function<void (bool& ,Node*)> f,std::function<void (Set<Node*> &, const Node &) > successors){
      Set<Node *> list = this;
      int cycles =0;
      while(list){
        // get first element
        Node * current = list.first();
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
    // overlaod
    int Node::bfs(std::function<void (bool& ,Node*)> f){
      std::function<void (Set<Node*> &, const Node &) > sfunc = [](Set<Node *>& successors,const Node & node){        successors |= node.successors();      };
      return bfs(f,sfunc);
    }
    namespace nspace{
    // prints the suceeding graph to the output stream reference
    std::ostream &  operator << (std::ostream & c, Node& node){
      node.set("level",0);
      node.dfs([&c](bool & cont, Node * n){
        int level = n->get<int>("level");

        for(int j=0; j < level*2; j++)c <<" ";

        c <<n->name() <<std::endl;

        for(unsigned int i=0; i < n->entries();i++){
          Entry * entry = n->entries()(i);
          for(int j=0; j < level*2+1; j++)c <<" ";
          c << entry->name << std::endl; 
        }

        for(unsigned int i=0; i < n->successors(); i++){
          n->successors()(i)->set("level",level+1);
        }

      });
      return c;
    }
    }
    // callback when an element is added to the node. makes sure that the nodes are connected in both directions
    void Node::elementAdded(ObservableCollection<Node*> * sender, Node * node){
      if(sender == &_predecessors){
        // makes sure that the new nodes successor is set to this
        node->successors().add(this);
        // call extension point
        onPredecessorAdded(node);
      }else
        if(sender==&_successors){
          // make sure that the new nodes predecessor is set to this
          node->predecessors().add(this);
          onSuccessorAdded(node);
        }
        notifyElementAdded(node);
    }
    // callback when an element is removed from the node. makes sure the nodes are removed
    void Node::elementRemoved(ObservableCollection<Node*> * sender, Node * node){
      if(sender == &_predecessors){
        node->successors().remove(this);
        onPredecessorRemoved(node);
      }else
        if(sender==&_successors){
          node->predecessors().remove(this);
          onSuccessorRemoved(node);
        }
        notifyElementRemoved(node);
    }
