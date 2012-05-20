#include "TextileAlgorithm.h"

#include <algorithm>


using namespace std;
using namespace IBDS;


void TextileAlgorithm::normalize(){
  for_each(objects().begin(), objects().end(), [](TextileModel* model){
    model->normalize();
  });
}