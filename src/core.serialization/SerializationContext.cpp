#include "SerializationContext.h"

using namespace nspace::core::serialization;
SerializationContext::SerializationContext():idCounter(1){
}
int SerializationContext::getId(void* ptr){
  auto it = pointerIds.find(ptr);
  if(it==std::end(pointerIds))return 0;
  return it->second;
}
int SerializationContext::getId(std::shared_ptr<void> ptr){
  return getId(ptr.get());
}
int SerializationContext::requireId(void* ptr){
  auto id = getId(ptr);
  if(!id){
    pointerIds[ptr] = idCounter++;      
    id=getId(ptr);
  }
  return id;
}
int SerializationContext::requireId(std::shared_ptr<void> ptr){
  return requireId(ptr.get());
}

void SerializationContext::incrementProgress(int count){
  std::cerr<<"SerializationContext::incrementProgress not implemented trivial function"<<std::endl;
}
void SerializationContext::incrementTotalProgress(int count){
  std::cerr<<"SerializationContext::incrementTotalProgress not implemented trivial function"<<std::endl;
}