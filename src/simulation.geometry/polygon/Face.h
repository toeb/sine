#pragma once

#include <simulation.geometry/polygon/Element.h>
#include <simulation.geometry/polygon/HalfEdge.h>
#include <math/core.h>

namespace nspace{

struct Face: public Element{
    Vector3D n_ocs;
    int vertexCount;
    HalfEdge * first;
    bool valid;
    Face():first(0),valid(false){}
    void getCenter(Vector3D & c)const;
    void getVertices(std::vector<Vertex *> & vertices)const;
};

}
