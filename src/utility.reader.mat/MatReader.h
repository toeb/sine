#pragma once

#include <utility.reader.h>
#include <utility.reader.mat/MatFile.h>
namespace nspace{
  

class MatReader:public Reader{
public:
  typedef std::shared_ptr<MatFile> basic_property(Result);
protected:
  bool doRead()override final;
};
}