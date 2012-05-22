#include "TextileAlgorithm.h"

#include <algorithm>


using namespace std;
using namespace IBDS;

Real TextileAlgorithm::getSuggestedStepSize(){
  Real T_0_min=999999999;
  for_each(objects().begin(), objects().end(), [&T_0_min](TextileModel* model){
    if(T_0_min > model->getSuggestedStepSize())T_0_min=model->getSuggestedStepSize();
  });
  return T_0_min;
}

void TextileAlgorithm::normalize(){
  for_each(objects().begin(), objects().end(), [](TextileModel* model){
    model->normalize();
  });
}