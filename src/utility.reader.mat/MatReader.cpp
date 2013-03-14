#include "MatReader.h"

using namespace nspace;


bool MatReader::doRead(){
  if(!stream())return false;
  setResult(std::shared_ptr<MatFile>(new MatFile()));



  auto result = getResult();
  std::getline(stream(),result->Header(),'\0');

  // is it an error if \0 is missing and header text ends at <124?  -- check pls
  stream().seekg(0,stream().beg);
  stream().seekg(124,stream().beg);
  // get version and endianes(starts at byte 124)
  char m,i;
  char version1,version2;
  stream()>>version1>>version2>>m>>i;

  // if i m are reverse then byte swapping needs to occur.
  bool swap = i=='M'&&m=='I';
  result->setAreBytesSwapped(swap);


  int count=0;
  while((bool)stream()){
    ElementHeader header(result);
    binaryRead(header.type,swap,stream());      
    binaryRead(header.byteSize,swap,stream());      
    auto data = std::shared_ptr<char>(new char[header.byteSize]);
    stream().read(data.get(),header.byteSize);

    result->addElement(header,data);

    reportProgress(stream().tellg());
  }





  return true;

}