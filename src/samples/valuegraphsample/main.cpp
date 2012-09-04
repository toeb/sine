#include <utility/valuegraph/valuegraph.h>
#include <iostream>
using namespace nspace;
using namespace std;
int main(int argc, const char * argv){

  TypedObservableValue<int> a =0;
  ValueHistory<int>  history(a);

  a.addObserver(new ValueObserverDelegate([&history](void * sender){
    cout << history <<endl;
  }));
  for(int i=0; i < 20; i++)a.set(i);
}