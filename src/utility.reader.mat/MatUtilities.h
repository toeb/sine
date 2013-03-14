#pragma once
#include <istream>
namespace nspace{
  
  typedef unsigned __int16 uint16;
  typedef unsigned __int32 uint32;
  struct membuf : std::streambuf
  {
    membuf(char* begin, char* end) {
      this->setg(begin, begin, end);
    }
  };

  bool isLittleEndian();

  template<typename T>
  bool binaryRead(T & value,const bool swapOrder, std::istream & stream){  
    static const unsigned int size=sizeof(T);
    union{
      char bytes[size];
      T value;
    }data;
    auto pos = stream.tellg();
    auto result = stream.readsome((char*)&data,size);
    if(result!=size){
      stream.seekg(pos);
      return false;
    }

    if(swapOrder!=isLittleEndian()){
      for(int i=0; i < size/2;i++){     
        std::swap( data.bytes[i], data.bytes[size-i-1]);
      }
    }
    value = data.value;
    return true;
  }

}