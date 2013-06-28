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
    reflect_type(nspace::UnitTest);

    reflect_method(RunTest);
    void RunTest();


    typedef std::string reflect_property( TestName);
    typedef std::string reflect_property( TestDescription);
    typedef SourceInfo* reflect_property( Info);
    typedef bool        reflect_property( IsInitialized);
    typedef double      reflect_property( Time);
    typedef int         reflect_property( FailedTests);
    typedef time_t      reflect_property( TestStartTime);
    typedef time_t      reflect_property( TestEndTime);

    PROPERTYSET(UnitTestResult*, Results,,);
    //@todo rename to ... (failures)
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