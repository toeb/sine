using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication2
{
  class Program
  {
    static void Main(string[] args)
    {
      int argumentCount = 3;


      //Console.WriteLine(implementation(true, false, true, argumentCount));
      //Console.WriteLine(implementation(true, false, false, argumentCount));




      Console.WriteLine(generate(argumentCount));
      File.WriteAllText("TypedCallableInfo.h", generate(10));
      File.WriteAllText("make_types.h", generateConstructorSignatures(10));
      File.WriteAllText("signature_discriminator.h", generateSignatureDiscriminators(10));
      File.WriteAllText("TypedConstructorInfo.h", generateTypedConstructorInfo(10));
      File.WriteAllText("constructor.h", generateConstructorDecls(10) + "\n\n" + generateConstructorDefs(10));


      File.WriteAllText("callable_traits.h", generate_callable_traits(10));

      File.WriteAllText("type_tuple.h", generate_tuples(10));
      File.WriteAllText("template_argument.h", generate_typeargs(10));

    }

    private static string generate_tuple(int n, int max)
    {
      string result = "";

      result += templateArgs(args(n), true, true);
      if (n == max)
      {
        for (int i = 0; i < max; i++)
        {
          result = result.Replace(argName(i), argName(i) + "=nspace::Nil");
        }
      }
      result += "\nstruct type_tuple";
      if (n != max)
      {
        result += "<";
        result += templateArgs(args(n), false, false);
        if (n > 0) result += ", ";
        for (int i = n; i < max; i++)
        {
          result += "nspace::Nil";
          if (i != max - 1) result += ", ";
        }
        result += ">";
      }
      result += "{\n";
      result += "static const size_t size =" + n + ";\n";
      result += "template<size_t i> \nstruct at:public template_argument<i"
        + (n == 0 ? "" : ", ")
        + templateArgs(args(n), false, false) + ">{};\n";

      result += "template<typename Functor>\nstatic void for_each(Functor & functor){\n";
      for (int i = 0; i < n; i++)
      {
        result += "functor.operator()<" + argName(i) + ", "+i+">();\n";
      }
      result += "}\n";
      result += "};\n";
      return result;

    }
    private static string generate_tuples(int n)
    {
      string result = @"#pragma once
#include <config.h>
#include <core/template/template_argument.h>
namespace nspace{
";
      for (int i = n; i >= 0; i--)
      {
        result += generate_tuple(i, n) + "\n";
      }
      result += "\n}\n";
      return result;

    }

    private static string generate_typearg(int n, int max)
    {
      string result = "";
      result += "template<";
      if (n == max) result += "size_t index, ";
      result += templateArgs(args(max), true, false);
      if (n == max)
      {
        for (int i = 0; i < n; i++)
        {
          result = result.Replace(argName(i), argName(i) + "=nspace::Nil");
        }
      }
      result += ">\n";
      result += "struct template_argument";
      if (n != max)
      {
        result += "<";
        result += n + ", ";
        result += templateArgs(args(max), false, false);
        result += ">";
      }
      result += "{\n";
      if (n != max) result += "typedef " + argName(n) + " type;\n";
      else result += "typedef nspace::Nil type;\n";
      result += "};\n";


      return result;

    }
    private static string generate_typeargs(int n)
    {
      string result = @"#pragma once
#include <config.h>
namespace nspace{
";
      for (int i = n; i >= 0; i--)
      {
        result += generate_typearg(i, n) + "\n";
      }
      result += "\n}\n";
      return result;

    }
    private static string generate_call_methods(int n)
    {
      string result = "";

      return result;
    }
    private static string generate_call_method(int n)
    {

      string result = "";

      return result;
    }

    private static string generate_callable_traits(int n)
    {
      string result = "";

      result += @"#pragma once
#include <config.h>
#include <tuple>
#include <iterator>
#include <memory>
#include <core/template/type_tuple.h>
namespace nspace{
// default implementation assumes that Callable is a functor - only works for types with single operator()
  // overloaded operators are not supported
  template<typename Callable>
  struct callable_traits:public callable_traits<decltype(&Callable::operator())>{  
    static const bool is_functor = true;
    template<typename TContainer>
    static auto call(const Callable & callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      // decay type because it would be a reference
      typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;
      std::vector<argument_type> args;      
      args.push_back(&callable);    
      args.insert(args.end(),std::begin(container),std::end(container));
      return callable_traits<decltype(&Callable::operator())>::call(&Callable::operator(),args);
    }
    // assumes that the first element in container is the functor object and the following are its parameters
    template<typename TContainer>
    static auto call(const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
      return callable_traits<decltype(&Callable::operator())>::call(&Callable::operator(),container);
    }
  };

//calls any callable with any container of arguments (arguments can be converted from and to any type inkl rvalues)
// expects first argument to be a pointer to the correct object if is_member is true
 template<typename Callable,typename TContainer>
  auto call_callable(Callable & callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{
    return callable_traits<Callable>::call(callable, container);
  }
";

      for (int i = 0; i < n; i++)
      {
        result += "// callable traits for " + i + " arguments\n";
        result += generate_callable_trait(i, true, true, false) + "\n";
        result += generate_callable_trait(i, true, true, true) + "\n";
        result += generate_callable_trait(i, true, false, false) + "\n";
        result += generate_callable_trait(i, true, false, true) + "\n";
        result += generate_callable_trait(i, false, false, false) + "\n";
        result += generate_callable_trait(i, false, false, true) + "\n";
      }
      result += "\n}\n";
      return result;


    }

    private static string generate_callable_trait(int n, bool isMember, bool isConst, bool isVoid)
    {
      string result = "";


      var elements = new List<string>();
      if (isMember) elements.Add("Class");
      if (!isVoid) elements.Add("ReturnType");

      result = templateArgs(elements.Concat(args(n)), true, true) + "\n";

      result += "struct callable_traits<";
      result += callableSignature(isConst, isMember, isVoid, n);

      result += ">{\n";
      result += "typedef " + (isVoid ? "void" : "ReturnType") + " return_type;\n";
      result += "typedef " + callableSignature(isConst, isMember, isVoid, n, "callable_type") + ";\n";
      result += "static const bool is_functor=false;\n";
      result += "static const bool is_member=" + (isMember ? "true" : "false") + ";\n";
      result += "static const bool is_const=" + (isConst ? "true" : "false") + ";\n";

      result += "\nstruct arguments : public type_tuple<";
      if (n != 0) result += templateArgs(args(n), false, false);
      result += ">{\n};\n";
      result += "static const int expected_arguments = arguments::size + (is_member?1:0);\n";
      /*
            for (int i = 0; i < n; i++)
            {
              result += "typedef " + argName(i) + " argument_" + i + "_type;\n";
            }
            */


      result += "//expects a container of arguments. Arguments must be convertible to and from any type and rvalue reference to be generally available,\n//also it must have a static method called Void() which returns the argument for void\n";
      if (isMember) result += "//the first argument must be to a void * which points to a object of type Class\n";
      result += "template<typename TContainer>\n";
      result += "static auto call(callable_type callable, const TContainer & container)->typename std::decay<decltype(*std::begin(container))>::type{\n";
      result += "typedef typename std::decay<decltype(*std::begin(container))>::type argument_type;\n";
      result += "auto start = std::begin(container);\n";
      result += "auto end = std::end(container);\n";
      result += "if(std::distance(start,end)!=expected_arguments){\n";
      result += "  throw new std::exception(\"invalid call: expected argument count differs from actual argument count\");\n";
      result += "}\n";
      result += "auto it = start;\n";
      if (isMember)
      {
        if (isConst) result += "const ";
        result += "Class * object = (Class*)(void*)*it++;\n";
        result += "if(!object){\nthrow new std::exception(\"invalid call: first argument may not be null\");\n}\n";
      }
      if (!isVoid) result += "return ";
      result += "(";
      if (isMember) result += "object->";
      result += "*callable)(";

      for (int i = 0; i < n; i++)
      {
        result += "*it++";
        if (i != n - 1) result += ", ";
      }
      result += ");\n";
      if (isVoid) result += "return nspace::Void();\n";
      result += "}\n";






      result += "\n};\n";




      return result;
    }

    static IEnumerable<string> args(int end, int start = 0)
    {
      List<string> result = new List<string>();
      for (int i = start + 1; i <= end; i++)
      {
        result.Add(argName(i - 1));
      }
      return result;
    }
    public static string templateArgs(IEnumerable<string> items, bool withTypename, bool withBrackets)
    {
      string result = "";
      if (withBrackets && withTypename) result += "template";
      if (withBrackets) result += "<";
      for (int i = 0; i < items.Count(); i++)
      {
        if (withTypename) result += "typename ";
        result += items.ElementAt(i);

        if (i != items.Count() - 1) result += ", ";
      }
      if (withBrackets) result += ">";
      return result;
    }








    private static string generateConstructorDecl(int n, bool def)
    {
      string result = "";
      if (def)
      {
        result += "template<typename Class>\n";
      }
      if (n != 0)
      {
        result += "template<";
        result += templateHeaderArgs(n);
        result += ">\n";
      }
      result += "auto ";
      if (def)
      {
        result += "TypeBuilder<Class>::";
      }



      var constructorBuilderSig = "ConstructorBuilder<Class,TypedConstructorInfo<Class";
      for (int i = 0; i < n; i++)
      {
        if (i == 0) constructorBuilderSig += ", ";
        constructorBuilderSig += argName(i);
        if (i != n - 1) constructorBuilderSig += ", ";
      }


      constructorBuilderSig += ">>";
      result += "constructor()->std::shared_ptr<" + constructorBuilderSig + ">";

      if (def)
      {
        result += "{\n";
        result += "auto instance = std::make_shared<" + constructorBuilderSig + ">(this);\n";
        result += "instance->begin();\n";
        result += "return instance;\n";
        result += "};";
      }
      else
      {
        result += ";\n";
      }

      result += " \n\n";

      return result;
    }
    private static string templateHeaderArgs(int n)
    {
      string result = "";
      for (int i = 0; i < n; i++)
      {
        result += "typename " + argName(i);
        if (i != n - 1) result += ", ";
      }
      return result;
    }

    private static string generateConstructorDefs(int n)
    {

      string result = "";
      for (int i = 0; i < n; i++)
      {
        result += generateConstructorDecl(i, false);
      }
      return result;
    }
    private static string generateConstructorDecls(int n)
    {
      string result = "";
      for (int i = 0; i < n; i++)
      {
        result += generateConstructorDecl(i, true);
      }
      return result;
    }

    private static string generateTypedConstructorInfo(int p)
    {
      string result = @"#pragma once
#include <core.reflection/member/constructor/ConstructorInfo.h>
#include <core.reflection/callable/TypedCallableInfo.h>
#include <core/template/make_types.h>
namespace nspace{
// contains typed constructor info for constructors with up to " + p + @" arguments
";
      result += "template<typename Class";
      for (int i = 0; i < p; i++)
      {
        result += ", typename ";
        result += argName(i);
        result += " = nspace::Nil";
      }
      result += ">\n";
      result += "struct TypedConstructorInfo\n";

      string templateArgs = "<Class";
      string templateArgs2 = "<";
      for (int i = 0; i < p; i++)
      {
        templateArgs += argName(i);
        templateArgs2 += argName(i) + "&& ";
        if (i != p - 1)
        {
          templateArgs += ", ";
          templateArgs2 += ", ";
        }
      }
      templateArgs2 += ">";
      templateArgs += ">";

      var innerStart = "shared_callable(static_signature" + templateArgs2 + "(";
      var innerEnd = "))";

      result += ":public ConstructorInfo{\nTypedConstructorInfo(){\n";
      result += "setMakeShared(" + innerStart + "&make<Class>::shared_" + p + templateArgs + innerEnd + ");\n";
      // result += "setMakeUnique(" + innerStart + "&make<Class>::unique_" + p + templateArgs + innerEnd + ");\n";
      result += "setMakeRaw(" + innerStart + "&make<Class>::raw_" + p + templateArgs + innerEnd + ");\n";
      innerStart = innerStart.Replace("static_signature<", "static_signature<void*");
      if (p != 0) innerStart += ", ";
      result += "setMakePlacement(" + innerStart + "&make<Class>::placement_" + p + templateArgs + innerEnd + ");\n";
      result += "}\n};\n";



      for (int i = 0; i < p; i++)
      {
        result += generateTypedConstructorInfo(i, p);
      }

      result += "}";
      return result;
    }

    private static string generateTypedConstructorInfo(int n, int p)
    {
      string result = "";
      result += "template <typename Class";
      for (int i = 0; i < n; i++)
      {
        result += ", typename ";
        result += argName(i);
      }
      result += ">\n";
      result += "struct TypedConstructorInfo<Class";
      for (int i = 0; i < p; i++)
      {
        if (i < n)
        {
          result += ", " + argName(i);
        }
        else
        {
          result += ", nspace::Nil";
        }
      }

      result += ">";




      string templateArgs = "<";
      string templateArgs2 = "<";

      for (int i = 0; i < n; i++)
      {
        templateArgs += argName(i);
        templateArgs2 += argName(i) + "&& ";
        if (i != n - 1)
        {
          templateArgs += ", ";
          templateArgs2 += ", ";
        }
      }
      templateArgs2 += ">";
      templateArgs += ">";

      if (n == 0)
      {
        templateArgs2 = "";
        templateArgs = "";
      }

      var innerStart = "shared_callable_info(static_signature" + templateArgs2 + "(";
      var innerEnd = "))";

      result += ":public ConstructorInfo{\nTypedConstructorInfo(){\n";
      result += "setMakeShared(" + innerStart + "&make<Class>::shared_" + n + templateArgs + innerEnd + ");\n";
      // result += "setMakeUnique(" + innerStart + "&make<Class>::unique_" + n + templateArgs + innerEnd + ");\n";
      result += "setMakeRaw(" + innerStart + "&make<Class>::raw_" + n + templateArgs + innerEnd + ");\n";
      if (n == 0)
      {
        innerStart = innerStart.Replace("static_signature", "static_signature<void*>");
      }
      else
      {
        innerStart = innerStart.Replace("static_signature<", "static_signature<void*, ");
      }

      result += "setMakePlacement(" + innerStart + "&make<Class>::placement_" + n + templateArgs + innerEnd + ");\n";
      result += "}\n};\n";



      return result;
    }





    static string generateSignatureDiscriminators(int n)
    {
      string result = "";

      result = "#pragma once\n#include <config.h>\nnamespace nspace{\n//this file contains static functions for discriminating signatures of overloaded functions with up to + " + (n - 1) + " arguments\n";

      for (int i = 0; i < n; i++)
      {
        result += "// discriminators for " + i + " arguments\n";
        result += signatureDiscriminator(true, true, i);
        result += signatureDiscriminator(false, true, i);
        result += signatureDiscriminator(false, false, i);
      }
      result += "}\n";
      return result;
    }

    static string signatureDiscriminator(bool isConst, bool isMember, int n)
    {

      string result = "";
      result += "template<";
      for (int i = 0; i < n; i++)
      {
        result += "typename " + argName(i) + ", ";

      }
      if (isMember) result += "typename Class, ";
      result += "typename ReturnType";

      result += ">\ninline auto ";
      if (!isMember)
      {
        result += "static_";
      }
      else if (isConst)
      {
        result += "const_";
      }
      result += "signature(" + callableSignature(isConst, isMember, false, n, "signature_ptr") + ")->"
        + callableSignature(isConst, isMember, false, n) + "{\n";
      result += "return signature_ptr;\n";
      result += "}\n\n";

      return result;
    }
    static string generateConstructorSignatures(int n)
    {
      string result = @"
#pragma once
#include <memory>
#include <config.h>
namespace nspace{
template<typename Class>
struct make{
//construction methods for up to " + (n - 1) + " arguments\n";

      for (int i = 0; i < n; i++)
      {
        result += "//constructor methods for " + i + " arguments \n";
        result += generateConstructorSignature("raw", i);
        result += generateConstructorSignature("shared", i);
        result += generateConstructorSignature("placement", i);
        result += generateConstructorSignature("unique", i);

        result += generateConstructorSignature("raw", i, "_" + i);
        result += generateConstructorSignature("shared", i, "_" + i);
        result += generateConstructorSignature("placement", i, "_" + i);
        result += generateConstructorSignature("unique", i, "_" + i);
      }
      result += "};\n}\n";
      return result;
    }
    static string generateConstructorSignature(string type, int n, string nameExtra = "")
    {
      string result = "";
      result += "template<";
      for (int i = 0; i < n; i++)
      {
        result += "typename " + argName(i);
        if (n - 1 != i) result += ", ";
      }
      result += ">";
      if (result.EndsWith("<>")) result = "";


      result += "\n static inline ";
      switch (type)
      {
        case "shared":
          result += "std::shared_ptr<Class> ";
          break;
        case "raw":
          result += "Class * ";
          break;
        case "placement":
          result += "void ";
          break;
        case "unique":
          result += "std::unique_ptr<Class> ";
          break;
      }
      result += type + nameExtra + "(";
      if (type == "placement")
      {
        result += "void * address, ";
      }
      for (int i = 0; i < n; i++)
      {
        result += argName(i) + " && a" + i + ", ";
      }
      if (result.Last() != '(')
      {
        result = result.Substring(0, result.Length - 2);
      }
      result += "){\n";
      if (type != "placement") result += "return ";
      switch (type)
      {
        case "shared":
          result += "std::make_shared<Class>";
          break;
        case "raw":
          result += "new Class";
          break;
        case "placement":
          result += "new (address) Class";
          break;
        case "unique":
          result += "std::unique_ptr<Class>( new Class";
          break;
      }
      result += "(";
      for (int i = 0; i < n; i++)
      {
        result += "a" + i;
        if (i != n - 1) result += ", ";
      }
      result += ")";
      if (type == "unique") result += ")";
      result += ";\n";
      result += "}\n";

      return result;

    }


    static string generate(int n)
    {
      string result = "";

      result += "#pragma once\n";
      result += "#include <core.reflection/callable/TypedCallableInfoBase.h>\n#include <memory>\n#include <core/template/signature_discriminator.h>\n";
      result += "namespace nspace{\n";
      result += "template<typename Callable>\nstruct TypedCallableInfo{};\n";

      for (int i = 0; i < n; i++)
      {
        result += "// specializations for " + i + " args\n";
        result += implementation(true, true, true, i);
        result += implementation(true, true, false, i);
        result += implementation(false, true, true, i);
        result += implementation(false, true, false, i);
        result += implementation(false, false, true, i);
        result += implementation(false, false, false, i);
      }
      result += @"
  template<typename T>
  TypedCallableInfo<T> callable_info(T info){
    return TypedCallableInfo<T>(info);
  }

  template<typename T>
  std::shared_ptr<TypedCallableInfo<T>> shared_callable_info(T callable){
    static auto info  = std::make_shared<TypedCallableInfo<T>>(callable);
    return info;
  }";

      result += "}\n";
      return result;
    }

    static string implementation(bool isConst, bool isMember, bool returnsVoid, int n)
    {


      string result = "// specialization for ";

      if (returnsVoid) result += "void valued ";
      if (isMember)
      {
        if (isConst)
        {
          result += "const ";
        }
        result += "member ";
      }
      else
      {
        result += "static ";
      }
      result += "method with " + n + " arguments";
      result += "\n";

      result += templateHeader(isConst, isMember, returnsVoid, n) + "\n";
      result += classSignature(isConst, isMember, returnsVoid, n) + "{\n";
      result += constructor(isConst, isMember, returnsVoid, n) + "\n";
      result += callImplementation(isConst, isMember, returnsVoid, n) + "\n";
      result += "};\n\n";

      return result;
    }
    static string argName(int i)
    {
      return "T" + i;
    }
    static string callableSignature(bool isConst, bool isMember, bool returnsVoid, int n, string name = "")
    {
      string result = "";
      if (!returnsVoid)
      {
        result += "ReturnType";
      }
      else
      {
        result += "void";
      }

      result += "(";
      if (isMember)
      {
        result += "Class::";
      }
      result += "*"+/*(isMember?"":"const ")+*/ name + ")(";

      for (int i = 0; i < n; i++)
      {
        result += argName(i);
        if (i != n - 1) result += ", ";
      }

      result += ")";

      if (isMember && isConst)
      {
        result += "const";
      }
      return result;
    }
    static string callImplementation(bool isConst, bool member, bool returnsVoid, int n)
    {
      string result = "Argument callImplementation(const ArgumentList & args)const{\n";

      result += "callable_type callable = Callable();\nArgument result;\n";


      if (member)
      {
        result += "Class * object = (Class*)(void*)args[0];\n";
      }

      if (!returnsVoid)
      {
        result += "result = ";
      }
      else
      {
        result += "result = Argument::VoidArgument();\n";
      }


      if (member)
      {
        result += "(object->*callable)";
      }
      else
      {
        result += "(*callable)";
      }

      result += "(";

      for (int i = (member ? 1 : 0); i < n + (member ? 1 : 0); i++)
      {

        result += "(" + argName(i - (member ? 1 : 0)) + ")" + "args[" + i + "]";
        if (i != n + (member ? 1 : 0) - 1) result += ", ";
      }
      result += ");\n";


      result += "return result;\n";
      result += "}\n";
      return result;
    }

    static string constructor(bool isConst, bool member, bool returnsVoid, int n)
    {
      string result = "TypedCallableInfo(callable_type callable):TypedCallableInfoBase(callable){\n";
      result += "setIsConst(" + (isConst && member ? "true" : "false") + ");\n";
      result += "setIsStatic(" + (!member ? "true" : "false") + ");\n";

      for (int i = 0; i < n; i++)
      {
        result += "Arguments().push_back(std::make_shared<nspace::TypedArgumentInfo<" + argName(i) + ", " + i + ">>());";
        result += "\n";
      }

      result += "}\n";
      return result;
    }

    static string classSignature(bool isConst, bool member, bool returnsVoid, int n)
    {
      string result = "struct TypedCallableInfo<";
      result += callableSignature(isConst, member, returnsVoid, n);
      result += "> : ";
      result += "public TypedCallableInfoBase<";
      result += callableSignature(isConst, member, returnsVoid, n);
      if (returnsVoid) result += ", void";
      else result += ", ReturnType";
      result += ">";
      return result;
    }

    static string templateHeader(bool isConst, bool member, bool returnsVoid, int n)
    {
      string result = "";

      List<string> typenames = new List<string>();

      if (!returnsVoid)
      {
        typenames.Add("ReturnType");
      }
      if (member)
      {
        typenames.Add("Class");
      }



      for (int i = 0; i < n; i++)
      {
        typenames.Add(argName(i));
      }

      result += "template<";
      for (int i = 0; i < typenames.Count; i++)
      {
        result += "typename " + typenames[i];
        if (i != typenames.Count - 1) result += ", ";
      }

      result += ">";
      return result;

    }


  }
}
