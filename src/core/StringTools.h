#pragma once

#include <string>

namespace std{
  namespace extensions{
    std::string operator +(const std::string & a, const std::string & b);
    std::string operator +(std::string a, const char * b);
    std::string operator +(const char * a, std::string b);

    std::string replace(std::string original, const std::string & search, const std::string & replacement);

  }
}