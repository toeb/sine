#pragma once
#include <simulation.geometry/polygon/Element.h>

namespace nspace{
  struct Edge;
  struct Face;
  struct Vertex;
  struct HalfEdge :public Element{
    HalfEdge():next(0),previous(0),edge(0),face(0){}
    HalfEdge* next;
    HalfEdge * previous;
    Edge * edge;
    Face * face;
    inline bool isConnected()const{
      return next && previous;
    }

    bool isForwardHalfEdge()const;
    bool isFirstHalfEdgeOfFace()const;
    HalfEdge * getPrevious()const;

    Vertex * getEndVertex()const;
    Vertex * getStartVertex()const;
    HalfEdge * getReverseHalfEdge()const;
    HalfEdge * getNextHalfEdgeOf(const Vertex * v)const;
  };
}
