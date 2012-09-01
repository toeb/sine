#pragma once
namespace mbslib{
class AxisParser : public NamedChildParser{
public:
  Vector3D direction;
  AxisParser(): NamedChildParser("axis"){

  }
protected:
  bool parseChild(XMLElement * axisElement){
    if(!parseVector(direction,axisElement->Attribute("xyz")))return false;
    return true;
  }
};
}