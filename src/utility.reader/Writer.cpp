/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#include "Reader.h"

#include <fstream>


using namespace nspace;
using namespace std;


void nspace::parseLineWise(std::istream & stream,std::map<std::string, std::function<void (std::istream & stream)> > & lookup,const bool& cancel){
  using namespace std;
  string line;
  string lineType;
  while(getline(stream,line)&&!cancel) {
    stringstream linestream(line);
    linestream>> lineType;
    if(lineType=="") continue;
    std::map<std::string, std::function<void (std::istream & stream)> >::const_iterator it;
    if((it= lookup.find(lineType))!=  lookup.end()) {
      it->second(linestream);
    }
  }
}

bool Reader::read(){
  stream().seekg(0,ios::end);
  auto e=long(stream().tellg());
  stream().seekg(0,ios::beg);
  double totalProgress = double(e);
  resetProgress(totalProgress);
  logInfo("Reading "<<e<<" bytes");
  bool result= runStatefulTask();
  logInfo("Read "<<e<<" bytes in "<<getRunTime()<<"s");
  logInfo("Read was "<<(result?"successfull":"unsuccessfull"));
  return result;
}

bool Reader::runTaskReturnSuccess(){
  if(!_stream)    {
    logError("No stream was set");
    return false;
  }
  bool result = doRead();
  _stream=0;
  return result;
}
void Reader::clearResult(){}

std::istream & Reader::stream(){
return *_stream;
}
bool Reader::readString(const std::string & str){
  std::stringstream stream(str);
  setStream(stream);
  return read();
}
bool Reader::readStream(istream & stream){ 
  setStream(stream);
  return read();
}

bool Reader::readFile(const std::string & filename){
  std::ifstream stream(filename);
  setStream(stream);
  bool result = read();
  stream.close();
  return result;
}
void Reader::setStream(std::istream & instream){
  _stream = &instream;

}


Reader:: Reader() : _stream(0){
  setAbort(false);
}

