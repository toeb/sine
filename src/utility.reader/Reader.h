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
  
  class IBuilder{
  public:

  };




  /**
   * \brief Parses a stream line wise. using the first word to look up a parse function per line
   *
   * \param [in]  stream  The stream.
   * \param [in]  lookup  The lookup.
   * \param cancel            (optional) the cancel flag (parsing stops once cancel false (useful for multithreading)).
   */
  void parseLineWise(std::istream & stream,std::map<std::string, std::function<void (std::istream & stream)> > & lookup,const bool& cancel=false);
  
class ProgressReporter : public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(ProgressReporter);
  PROPERTY(double, NumberOfNotifications){
    if(newvalue==0)newvalue=1.0;
  }
  PROPERTY(double,TotalProgress){
    setNotificationInterval(newvalue/getNumberOfNotifications());
  }
  PROPERTY(double,Progress){
        
  }
  PROPERTY(double,NotificationInterval){}
  PROPERTY(bool, LogProgress){}
public:
  ProgressReporter():_NumberOfNotifications(200.0),_TotalProgress(1),_Progress(0),_NotificationInterval(0.01),_LogProgress(true){
    resetProgress();
  
  };
  double percent()const{
    return quotient()*100.0;
  }
  double quotient()const{
    return getProgress()/getTotalProgress();
  }

private:
  double _lastNotification;
protected:
  void resetProgress(double totalProgress){
    resetProgress();
    setTotalProgress(totalProgress);
  }
  void resetProgress(){
    _lastNotification=0;
    setProgress(0.0);  
  }
  void incrementProgress(double value){
    reportProgress(getProgress()+value);
  }
  void reportProgress(double value){
    _Progress = value;
    if(getProgress()>_lastNotification+getNotificationInterval()){
      _lastNotification=getProgress();
      notifyProgressChanged();
      if(getLogProgress()){
        logInfo("Progress: "<< percent() << "%");
      }
    }    
  }
};
  /**
  * \brief Reader superclass.
  */
class Reader : public virtual StatefulTask ,public virtual ProgressReporter{
    REFLECTABLE_OBJECT(Reader);
    SUBCLASSOF(StatefulTask);
    PROPERTY(bool, Abort){}
    REFERENCE(protected,bool,Abort);

  protected:
    virtual bool doRead()=0;
    std::istream & stream();
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
