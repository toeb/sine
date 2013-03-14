#include <core.testing.h>
#include <utility.reader.mat.h>

#include <istream>

using namespace nspace;




UNITTEST(ReadMatHeader){
  MatReader reader;
  auto result = reader.readFile("matlab/train_data.mat");
  CHECK(result);
}