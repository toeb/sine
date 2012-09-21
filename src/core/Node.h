#pragma once

#include <core/Set.h>
#include <core/NamedObject.h>
#include <core/ValueLookup.h>
#include <core/Comparator.h>

namespace nspace{

/**
 * \brief Node.forward declaration for comparator
 */
class Node;

/**
 * \brief Comparator specialization. for comparing a const char * to a node
 *
 * \tparam  Node *        Type of the node *.
 * \tparam  const char *  Type of the constant character *.
 */
template<> class Comparator< Node *, const char *>{
public:
  static void operation(bool & result, const Node * a, const char * b);
};



  /**
   * \brief Directional node. can have multiple predecessors as well as successors
   * 				
   * 				utilises set
   */
  class Node : public ValueLookup, public NamedObject, public ObservableCollection<Node*>, public ObservableCollection<Node*>::Observer{
  private:
    Set<Node*> _predecessors;
    Set<Node*> _successors;
  public: 
    Node(){
      _predecessors.addObserver(this);
      _successors.addObserver(this);
    }
    // creates  named node
    Node(const std::string & name){
      setName(name);
      _predecessors.addObserver(this);
      _successors.addObserver(this);
    }

    // destroys node. causing all connected nodes to be disconnected
    ~Node(){_predecessors.clear(); _successors.clear();}

    // all connected nodes (union of predecessors and successors)
    Set<Node*> neighbors()const{return predecessors()|successors();};
    
    
    const Set<Node*> & predecessors()const{
      return _predecessors;
    }
    
    Set<Node*> & predecessors(){
      return _predecessors;
    }


    const Set<Node*> & successors()const{
      return _successors;
    }

     Set<Node*> & successors(){
      return _successors;
    }

     // adds a set of predecessors (arrows indicate direction of connection
     Node & operator <<(const Set<Node*> & nodes){
       predecessors() |= nodes;
       return *this;
     }
     // adds a set of successors 
     Node & operator >>(const Set<Node*> & nodes){
       successors() |= nodes;
       return *this;
     }
     // adds a single predecessor
     Node & operator <<(Node & node){
       predecessors().add(&node);
       return *this;
     }
     //adds a single successor
     Node & operator >>(Node & node){
       successors().add(&node);
       return *this;
     }
     // adds a single predecessor (by pointer)
     Node & operator <<(Node * node){
       predecessors().add(node);
       return *this;
     }
     // adds a single successor (by pointer)
     Node & operator >>(Node * node){
       successors().add(node);
       return *this;
     }
     // overload for dfs(f,successors)
     void dfs(std::function<void (bool & , Node *)> f){
       dfs(f,[](Set<Node *>& successors,const Node & node){ successors |= node.successors(); });
     }
    // really bad implementation of dfs, it is slow and will crash if there are cycles in the graph
    void dfs(std::function<void (bool & , Node *)> f, std::function<void (Set<Node*> &, const Node &) > successors){
      
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
    int bfs(std::function<void (bool& ,Node*)> f,std::function<void (Set<Node*> &, const Node &) > successors=0){
      if(!successors)successors = [](Set<Node *>& successors,const Node & node){
        successors |= node.successors();
      };

       
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

    // prints the suceeding graph to the output stream reference
     friend std::ostream &  operator << (std::ostream & c, Node& node){
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
  protected:
    // callback when an element is added to the node. makes sure that the nodes are connected in both directions
    void elementAdded(ObservableCollection<Node*> * sender, Node * node){
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
    void elementRemoved(ObservableCollection<Node*> * sender, Node * node){
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
    virtual void onPredecessorAdded(Node * predecessor){}
    virtual void onSuccessorAdded(Node * successor){}
    virtual void onPredecessorRemoved(Node* predecessor){}
    virtual void onSuccessorRemoved(Node * predecessor){}

  };



}