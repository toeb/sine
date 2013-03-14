#pragma once


#include <utility.reader.mat/MatElementHeader.h>
#include <utility.reader.mat/MatElement.h>
namespace nspace{



struct MatFile{  
  reflect_type(MatFile);


  typedef std::string reflect_property(Header);
  typedef uint32 reflect_property(ByteSize);
  typedef uint32 reflect_property(Version);
  typedef bool reflect_property(AreBytesSwapped);
  typedef std::vector<std::shared_ptr<MatElement>> reflect_property(Elements);
public:
  property_reference(Header);
  property_reference(ByteSize);
  property_reference(Version);
  property_reference(AreBytesSwapped);
  property_reference(Elements);
  bool addElement(ElementHeader header, std::shared_ptr<char> rawData);

};

}