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
  * 				utilizes set
  */
  class Node : public ValueLookup, public NamedObject, public ObservableCollection<Node*>, public ObservableCollection<Node*>::Observer{
  private:
    // stores all direct predecessors
    Set<Node*> _predecessors;
    // stores all direct successors
    Set<Node*> _successors;
  public: 
    // creates a unnamed node
    Node();
    // creates  named node
    Node(const std::string & name);
    // destroys node. causing all connected nodes to be disconnected
    ~Node();
    // all connected nodes (union of predecessors and successors)
    Set<Node*> neighbors()const;
    // read access to predecessors
    const Set<Node*> & predecessors()const;
    // read write access to predecessors
    Set<Node*> & predecessors();
    // read write access to successor by index
    Node * successor(uint i);
    // read access to successor by index
    const Node * successor(uint i)const;
    //read / write access to predecessor by index
    Node * predecessor(uint i);
    // read access to predecessor by index
    const Node * predecessor(uint i)const;
    // read access tot first successor
    const Node * firstSuccessor()const;
    //read write access to first successor
    Node * firstSuccessor();
    // returns the first predecessor (const)
    const Node * firstPredecessor()const;    
    // returns the first predecessor
    Node * firstPredecessor();
    // allows const access to the successors
    const Set<Node*> & successors()const;
    //allows access to the successors
    Set<Node*> & successors();

    // adds a set of predecessors (arrows indicate direction of connection
    Node & operator <<(const Set<Node*> & nodes);
    // adds a set of successors 
    Node & operator >>(const Set<Node*> & nodes);
    // adds a single predecessor
    Node & operator <<(Node & node);
    //adds a single successor
    Node & operator >>(Node & node);
    // adds a single predecessor (by pointer)
    Node & operator <<(Node * node);
    // adds a single successor (by pointer)
    Node & operator >>(Node * node);


    // overload for dfs(f,successors)
    void dfs(std::function<void (bool & , Node *)> f);
    // depth first search order
    void dfs(std::function<void (bool & , Node *)> f, std::function<void (Set<Node*> &, const Node &) > successors);

    // breadth first search order (performancewise). returns the number of cycles found
    // successorFunction shall return the successors for the node ( for example let it return the predecessors if bfs is to be performed
    // on the predecessors
    int bfs(std::function<void (bool& ,Node*)> f,std::function<void (Set<Node*> &, const Node &) > successorFunction);
    // overload for bfs
    int bfs(std::function<void (bool& ,Node*)> f);

    // prints the suceeding graph to the output stream reference
    friend std::ostream &  operator << (std::ostream & c, Node& node);
  protected:
    // callback when an element is added to the node. makes sure that the nodes are connected in both directions
    void elementAdded(ObservableCollection<Node*> * sender, Node * node);
    // callback when an element is removed from the node. makes sure the nodes are removed
    void elementRemoved(ObservableCollection<Node*> * sender, Node * node);
    virtual void onPredecessorAdded(Node * predecessor){}
    virtual void onSuccessorAdded(Node * successor){}
    virtual void onPredecessorRemoved(Node* predecessor){}
    virtual void onSuccessorRemoved(Node * predecessor){}

  };



}