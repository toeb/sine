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
#include <ctime>
#include <core.testing/TestResult.h>


namespace nspace {

  /**
   * \brief Unit test. Clients need to implement test() method
   *
   */
  class UnitTest : public virtual StatefulTask, public virtual Log, public virtual Timer {
    REFLECTABLE_OBJECT(UnitTest);
    ACTION(RunTest);
    PROPERTY(std::string, TestName);
    OBJECTPOINTERPROPERTY(SourceInfo, Info);
    PROPERTY(bool, IsInitialized);
    PROPERTY(double, Time);
    OBJECTPOINTERCOLLECTION(UnitTestResult, Results,,);
    //@todo rename to ... (failures)
    PROPERTY(int, FailedTests);
    PROPERTY(time_t, TestStartTime);
    PROPERTY(time_t, TestEndTime);
public:
    UnitTest(const std::string  &name);
    ~UnitTest();
    void reset();
    virtual void test()=0;
    virtual void initialize();
    virtual void destroy();
    virtual void toString(std::ostream & out) const;
protected:
    bool runTaskReturnSuccess();

    virtual void runTest();

  };


}