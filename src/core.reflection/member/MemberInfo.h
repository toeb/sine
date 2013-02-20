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
#include <core.reflection/attribute/Attribute.h>
#include <core/Object.h>

namespace nspace {

  /**
   * \brief Information about a member.
   *        @TODO remove attributes like description/displayname etc.
   */
  class MemberInfo : public virtual AttributeTarget {
    //TYPED_OBJECT(MemberInfo);

    SIMPLE_PROPERTY(std::string, Name);
    REFERENCE_PROPERTY(std::string, Name);

    typedef bool basic_property(IsVisible);
    typedef const Type * basic_property( OwningType );

    //enum Accessibility{private,public,protected}
    //typedef Accessibility basic_property(Accessibility);

    /**
     * \brief Description of the member.
     *
     */
    typedef std::string basic_property(Description);

    /**
     * \brief Display name of the member
     */
    typedef std::string basic_property( DisplayName);

    /**
     * \brief Group name of the member
     *
     */
    typedef std::string basic_property( GroupName);
public:

    /**
     * \brief Default constructor.
     */
    MemberInfo();
    virtual ~MemberInfo();
  };
}
