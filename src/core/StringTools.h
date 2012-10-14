#pragma once

#include <string>
#include <sstream>
namespace nspace{
    std::string operator +(const std::string & a, const std::string & b);
    std::string operator +(std::string a, const char * b);
    std::string operator +(const char * a, std::string b);

    template<typename T>
    std::string operator +(const std::string & a, const T & t){
        std::stringstream s;
        s<<a<<t;
        return s.str();

    }

    std::string replace(std::string original, const std::string & search, const std::string & replacement);
    std::string spaces(unsigned int count);

}
