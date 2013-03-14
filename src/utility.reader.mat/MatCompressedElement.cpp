#include "MatCompressedElement.h"
#include "MatFile.h"
#include "MatElementFactory.h"
#define ZLIB_WINAPI 
#include <zlib.h>
using namespace nspace;



bool MatCompressedElement::doLoad(){
#ifndef ZLIB_H
  return false;
#else
  auto raw = getRawData();
  auto header = getHeader();
  auto owner = header.getOwner();
  auto swapBytes = owner->getAreBytesSwapped();
  uLongf uncompressedLength = 8;
  // uncompress the first eight bytes to get the length of uncompressed data
  Bytef begin[8];

  auto result = uncompress(begin,&uncompressedLength,(Bytef*)raw.get(),header.byteSize);
  //result should be a error
  membuf head((char*)begin+4,(char*)begin+8);
  std::istream headStream(&head);
  uint32 length;    
  binaryRead(length,swapBytes,headStream);
  // add 8 bytes since header is going to be read again
  uncompressedLength = length+8;
  // uncompress all
  auto uncompressedRaw = std::shared_ptr<char>(new char[uncompressedLength]);

  result =uncompress((Bytef*)uncompressedRaw.get(),&uncompressedLength,(Bytef*)raw.get(),header.byteSize);

  if(result!=Z_OK){
    // error
    //return false;
  }

  membuf sbuf((char*)uncompressedRaw.get(), (char*)uncompressedRaw.get() + uncompressedLength);
  std::istream uncompressedStream(&sbuf);
  ElementHeader uncompressedHeader;
  binaryRead(uncompressedHeader.type,swapBytes,uncompressedStream);
  binaryRead(uncompressedHeader.byteSize,swapBytes,uncompressedStream);
  _UncompressedElement =matElementFactory(uncompressedHeader,uncompressedRaw);

  return true;
#endif
}


