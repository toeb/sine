#include "Color.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace nspace;
map<string, Color*> & Color::_palette = *new map<string, Color*>();
const Color & Color::unknown= *new Color(0,0,0,1,"unknown");
int colors = Color::loadColors("resources/colors/palette.txt");

int Color::loadColors(const std::string &filename ){
  ifstream file(filename,ifstream::in);
  if(!file.good())return 0;
  int colorsLoaded = 0;
  while(file.good()){
    int r,g,b;
    std::string name;
    file >> r >>g>>b;

    getline(file,name);
    
    name = name.substr(1);
    _palette[name]=new Color(r,g,b,255,name);
    colorsLoaded++;
  }  
  return colorsLoaded;
}
namespace nspace{
std::ostream & operator <<(std::ostream & o, const Color & color){
  o << "[" << (int)color.r8bit() << ", " << (int)color.g8bit()<<", "<< (int)color.b8bit() << "] " << color.colorName().c_str();  
  return o;
}
}
