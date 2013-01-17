#pragma once

#include <utility.reader.h>
#include <map>
#include <rply/rply.h>

namespace nspace{

struct PlyElement;

struct PlyObject:public std::map<std::string,std::shared_ptr<PlyElement> >{
  std::vector<std::string> info;
  std::vector<std::string> comments;
};

struct PlyProperty;
struct PlyElement:public std::map<std::string,std::shared_ptr<PlyProperty> >{
  PlyObject & object;
  std::string name;
  long instances;
  PlyElement(PlyObject & object, const std::string & name, long instances);
};

struct PlyProperty{
  typedef size_t Index;
  std::string name;
  PlyElement & element;
  std::vector<std::pair<Index,double> > values;

  PlyProperty(const std::string & name, PlyElement &  element);
  void value(const Index i, double value);
};


class PrivatePlyReader;

class PlyReader : public Reader{
  REFLECTABLE_OBJECT(PlyReader);
  SUBCLASSOF(Reader);

  PROPERTY(bool, ReadComments){}
  PROPERTY(bool, ReadObjectInfo){}
  PROPERTY(bool, Cancel){}
  SIMPLE_PROPERTY(std::shared_ptr<PlyObject>, Result){}

  PrivatePlyReader* reader;
public:
  PlyReader();
  ~PlyReader();
protected:

  void clearResult();
  // returns a filename which can be opened by plyopen. (may be a temp file constructed from a stream)
  const char * filename();
  bool doRead();
  friend class PrivatePlyReader;
};


}