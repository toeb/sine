#pragma once

#define DS_INLINE inline

#define DS_EXPAND(X) X
#define DS_STRINGIFY_(A) #A
#define DS_STRINGIFY__(A) DS_STRINGIFY_(A)
#define DS_STRINGIFY(A) DS_STRINGIFY__(A)


  //helper macro.
#define DS_CONCAT_(A,B) A ## B
#define DS_CONCAT__(A,B) DS_CONCAT_(A,B)
  /**
  * \brief A macro for concatenating to Preprocessor Tokens
  *        this is used when A ## B does not work
  *
  * \param A.
  * \param B.
  */
#define DS_CONCAT(A,B) DS_CONCAT_(A,B)

  /**
  * \brief A macro that creates a lambda to concatenate a string using stream out operator <<
  *        evaluates to a std::string
  *
  * \param ARGS  The arguments.
  */
#define DS_INLINE_STRING(ARGS) (std::function<std::string ()>([&]()->std::string{std::ostringstream stream; stream << ARGS; return stream.str();})() )




// VA_ARG count for up to 100 arguments
#define DS_NUM_ARGS_(X100, X99, X98, X97, X96, X95, X94, X93, X92, X91, X90, X89, X88, X87, X86, X85, X84, X83, X82, X81, X80, X79, X78, X77, X76, X75, X74, X73, X72, X71, X70, X69, X68, X67, X66, X65, X64, X63, X62, X61, X60, X59, X58, X57, X56, X55, X54, X53, X52, X51, X50, X49, X48, X47, X46, X45, X44, X43, X42, X41, X40, X39, X38, X37, X36, X35, X34, X33, X32, X31, X30, X29, X28, X27, X26, X25, X24, X23, X22, X21, X20, X19, X18, X17, X16, X15, X14, X13, X12, X11, X10, X9, X8, X7, X6, X5, X4, X3, X2, X1, N, ...)   N
#define DS_NUM_ARGS(...) DS_EXPAND(DS_NUM_ARGS_(__VA_ARGS__, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

// FOREACH MACRO for up to 30 arguments
#define DS_FIRST(X, ...) X
#define DS_REST(X, ...) __VA_ARGS__



// Reduction of VA args list,  applies macro M to every element and adds SEPARATOR in between results
// DS_REDUCE(,+,1,2,3,4,5,6,7) evaluates to (1)+(2)+(3)+(4)+(5)+(6)+(7)

#define DS_REDUCE_1(M, SEPARATOR,X) M(X)
#define DS_REDUCE_2(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_1(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_3(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_2(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_4(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_3(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_5(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_4(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_6(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_5(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_7(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_6(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_8(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_7(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_9(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_8(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_10(M, SEPARATOR,...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) SEPARATOR DS_REDUCE_9(M,SEPARATOR,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_N(N, M, SEPARATOR, ...) DS_CONCAT(DS_REDUCE_,N)(M,SEPARATOR,__VA_ARGS__)
#define DS_REDUCE(M,SEPARATOR,...) DS_REDUCE_N(DS_NUM_ARGS(__VA_ARGS__),M,SEPARATOR,__VA_ARGS__)



#define DS_REDUCE_COMMA_1(M,X) M(X)
#define DS_REDUCE_COMMA_2(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_1(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_3(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_2(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_4(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_3(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_5(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_4(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_6(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_5(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_7(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_6(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_8(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_7(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_9(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_8(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_10(M, ...)  DS_EXPAND(M(DS_FIRST(__VA_ARGS__))) , DS_REDUCE_COMMA_9(M,DS_EXPAND(DS_REST(__VA_ARGS__)))
#define DS_REDUCE_COMMA_N(N, M,  ...) DS_CONCAT(DS_REDUCE_COMMA_,N)(M,__VA_ARGS__)
#define DS_REDUCE_COMMA(M,...) DS_REDUCE_COMMA_N(DS_NUM_ARGS(__VA_ARGS__),M,__VA_ARGS__)


