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

/**
 * \file  core\preprocessor\Basic.h
 *
 * \brief Declares the basic macros which are reused many times in the projects.
 */
#pragma once
/**
 * \brief A macro that defines inline .
 *        Subprojects of DS should use this macro to show define a method as inline so the inline directive can be altered more easily
 *
 */
#define DS_INLINE inline

/**
 * \brief A macro that defines expands the passed template argument.
 *        this is often used to enforce correct behaviour in boxed macros
 *
 * \param X The void to process.
 */
#define DS_EXPAND(X) X

/**
 * \brief A macro that stringifies a macro token.
 *
 *  Stringify is boxed, because in particular cases just using the stringifiy operator # alone will not work correclty
 *
 * \param A The void to process.
 */
#define DS_STRINGIFY_(A) # A
#define DS_STRINGIFY__(A) DS_STRINGIFY_(A)
#define DS_STRINGIFY(A) DS_STRINGIFY__(A)


/**
 * \brief A macro for concatenating two Preprocessor Tokens
 *        this is used when A ## B does not work
 *
 * \param A.
 * \param B.
 */
#define DS_CONCAT(A,B) DS_CONCAT_(A,B)
#define DS_CONCAT_(A,B) A ## B
#define DS_CONCAT__(A,B) DS_CONCAT_(A,B)

/**
 * \brief A macro that creates a lambda to concatenate a string using stream out operator <<
 *        evaluates to a std::string
 *
 * \param ARGS  The arguments.
 */
#define DS_INLINE_STRING(ARGS) (std::function<std::string ()>([&]()->std::string {std::ostringstream stream; stream << ARGS; return stream.str(); }) () )

/**
 * \brief A macro that defines no operation (it is replaced by X)
 *
 *
 * \param X The void to process.
 */
#define DS_NOOP(X) DS_EXPAND(X)




#define DS_SEQUENCE_0  0
#define DS_SEQUENCE_1   DS_SEQUENCE_0  , 1  
#define DS_SEQUENCE_2   DS_SEQUENCE_1  , 2  
#define DS_SEQUENCE_3   DS_SEQUENCE_2  , 3  
#define DS_SEQUENCE_4   DS_SEQUENCE_3  , 4  
#define DS_SEQUENCE_5   DS_SEQUENCE_4  , 5  
#define DS_SEQUENCE_6   DS_SEQUENCE_5  , 6  
#define DS_SEQUENCE_7   DS_SEQUENCE_6  , 7  
#define DS_SEQUENCE_8   DS_SEQUENCE_7  , 8  
#define DS_SEQUENCE_9   DS_SEQUENCE_8  , 9  
#define DS_SEQUENCE_10  DS_SEQUENCE_9  , 10 
#define DS_SEQUENCE_11  DS_SEQUENCE_10 , 11 
#define DS_SEQUENCE_12  DS_SEQUENCE_11 , 12 
#define DS_SEQUENCE_13  DS_SEQUENCE_12 , 13 
#define DS_SEQUENCE_14  DS_SEQUENCE_13 , 14 
#define DS_SEQUENCE_15  DS_SEQUENCE_14 , 15 
#define DS_SEQUENCE_16  DS_SEQUENCE_15 , 16 
#define DS_SEQUENCE_17  DS_SEQUENCE_16 , 17 
#define DS_SEQUENCE_18  DS_SEQUENCE_17 , 18 


#define DS_SEQUENCE(N) DS_CONCAT(DS_SEQUENCE_,N)



#define DS_MINUS_ONE_0  
#define DS_MINUS_ONE_1  0
#define DS_MINUS_ONE_2  1
#define DS_MINUS_ONE_3  2
#define DS_MINUS_ONE_4  3
#define DS_MINUS_ONE_5  4
#define DS_MINUS_ONE_6  5
#define DS_MINUS_ONE_7  6
#define DS_MINUS_ONE_8  7
#define DS_MINUS_ONE_9  8
#define DS_MINUS_ONE_10  9
#define DS_MINUS_ONE_11  10
#define DS_MINUS_ONE_12  11
#define DS_MINUS_ONE_13  12
#define DS_MINUS_ONE_14  13
#define DS_MINUS_ONE_15  14
#define DS_MINUS_ONE_16  15
#define DS_MINUS_ONE_17  16
#define DS_MINUS_ONE_18  17
#define DS_MINUS_ONE_19  18
#define DS_MINUS_ONE_20  19
#define DS_MINUS_ONE_21  20
#define DS_MINUS_ONE_22  21

#define DS_MINUS_ONE(N) DS_CONCAT(DS_MINUS_ONE_,N)