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
#pragma once

#include <core.h>
#include <core.task.h>
#include <core.logging.h>

#include <map>

namespace nspace {

  /**
   * \brief Parses a stream line wise. using the first word to look up a parse function per line
   *
   * \param [in]  stream  The stream.
   * \param [in]  lookup  The lookup.
   * \param cancel            (optional) the cancel flag (parsing stops once cancel false (useful for multithreading)).
   */
  void parseLineWise(std::istream & stream,std::map<std::string, std::function<void (std::istream & stream)> > & lookup,const bool& cancel=false);

  /**
  * \brief Reader superclass.
  */
  class Reader : public virtual StatefulTask {
    REFLECTABLE_OBJECT(Reader);
    SUBCLASSOF(StatefulTask);
    PROPERTY(bool, Abort){}
    REFERENCE(protected,bool,Abort);

  protected:
    virtual bool doRead()=0;
    virtual void clearResult();
  public:    
    Reader();
    bool readString(const std::string & str);
    bool readStream(std::istream & stream);
    bool readFile(const std::string & filename);
    
    void setStream(std::istream & instream);  
    bool read();
  private:
    bool runTaskReturnSuccess();
    std::istream * _stream;
  };
}