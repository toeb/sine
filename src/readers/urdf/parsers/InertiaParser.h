#pragma once
#include <utility/xml/NamedChildParser.h>
#include <math/definitions.h>

namespace nspace{
  
// parsers the single cild node of given element <inertia> 
class InertiaParser : public NamedChildParser{
public:
  InertiaParser():NamedChildParser("inertia"){inertia.setZero();}
  Matrix3x3 inertia;
protected:
  bool parseChild(XMLElement * inertiaElement){
    Real ixx,iyy,izz,ixy,ixz,iyz;
    ixx=ixy=ixz=iyy=iyz=izz=0;
    //get attribute values for the six entries of the symmtetric inertia matrix
    inertiaElement->QueryDoubleAttribute("ixx",&ixx);
    inertiaElement->QueryDoubleAttribute("iyy",&iyy);
    inertiaElement->QueryDoubleAttribute("izz",&izz);
    inertiaElement->QueryDoubleAttribute("ixy",&ixy);
    inertiaElement->QueryDoubleAttribute("ixz",&ixz);
    inertiaElement->QueryDoubleAttribute("iyz",&iyz);
    //set the whole inertia matrix
    inertia(0,0)=ixx;
    inertia(0,1)=ixy;
    inertia(0,2)=ixz;
    inertia(1,0)=ixy;
    inertia(1,1)=iyy;
    inertia(1,2)=iyz;
    inertia(2,0)=ixz;
    inertia(2,1)=iyz;
    inertia(2,2)=izz;
    return true;
  }
};

}