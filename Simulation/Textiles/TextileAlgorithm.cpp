#include "TextileAlgorithm.h"

#include <algorithm>


using namespace std;
using namespace IBDS;

Real TextileModule::getSuggestedStepSize(){
  Real T_0_min=REAL_MAX;
  for_each(objects().begin(), objects().end(), [&T_0_min](TextileModel* model){
    if(T_0_min > model->getSuggestedStepSize())T_0_min=model->getSuggestedStepSize();
  });
  return T_0_min;
}

void TextileModule::normalize(){
  tick();

  for_each(objects().begin(), objects().end(), [](TextileModel* model){
    model->normalize();
  });

  tock();
}