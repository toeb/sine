#include "MatElementFactory.h"
#include "MatCompressedElement.h"
#include "MatPrimitiveElement.h"
#include "MatMatrixElement.h"
using namespace nspace;



namespace nspace{
  std::shared_ptr<MatElement> matElementFactory(ElementHeader header, std::shared_ptr<char> rawData){
    std::shared_ptr<MatElement> result;
    switch(header.type){
    case ElementHeader::miCOMPRESSED:      
      result = std::shared_ptr<MatCompressedElement>(new MatCompressedElement());
      break;
    case ElementHeader::miMATRIX:
      result = std::shared_ptr<MatMatrixElement>(new MatMatrixElement());
      break;
    case ElementHeader::miDOUBLE:
      result = std::shared_ptr<MatPrimitiveElement<double>>(new MatPrimitiveElement<double>());
      break;
    case ElementHeader::miINT32:
      result = std::shared_ptr<MatPrimitiveElement<__int32>>(new MatPrimitiveElement<__int32>());
      break;
    }
    if(!result->load(header,rawData))return std::shared_ptr<MatElement>();
    return result;
  }

}