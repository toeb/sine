#include <core.testing.h>

#include <utility.imaging/Image.h>
using namespace nspace;
TEST(Png1,ReadImage){
  auto file = "test128x128.png";
  PngImage img;
  CHECK(img.load(file));  
}

