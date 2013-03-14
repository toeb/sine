#pragma once

#include <utility.reader.mat/MatElement.h>

namespace nspace{
  

std::shared_ptr<MatElement> matElementFactory(ElementHeader header, std::shared_ptr<char> rawData);


}