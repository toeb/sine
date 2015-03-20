# sine


## The Documentation was just transferred from assembla.  It is in dissarray




The feature list that follows is by no way a gaurantee that the feature works or even exists.  In some cases I should have rather called it  a wishlist instead of feature list.  Nevertheless the library contains at least sketchy code for most of the feautres listed here:


Macros for Uniform Property definitions
C++ Reflection (without using an external meta data generator)
Types
Type Hierarchy
Properties
Actions (void(void) methods)
Attributes
Methods(any arguments and return types) (planned)
Qt User Interface
A simple plugin application (currently statically compiled)
Plugin Discovery (planned)
Sample Application (base for creating simple sample apps)
Object view (A view which uses reflection to automatically generate the ui)
Math
Matrix Library with generic operations
scalars are treated as matrices
currently following functions are implementable for  any type (custom types need to specialize the corresponding classes):
indexTypeOfType, indexTypeOfInstance
coefficientTypeOfType, coefficientTypeOfInstance
rows(matrix)
cols(matrix)
coefficient(matrix, i,j), coefficient(matrix,i), ...
assignMatrix(lhs,rhs), assingMatrixBlindly, assignMatrixForced
To allow custom matrix types specializations for OperationRowCount,OperationColumnCount, OperationCoefficientAccess need to be written
Lambda matrix. [](index i,index j)->scalar
Bindings for Eigen3
My own Matrix implementation
Convolution/Image Filters
A generic Set
easy to use operations like |= |, & ^ which apply the mathematical set operations 
general collection library (planned)
Simulation 
Integrators
System State management
Concurrent Simulations (planned)
Visualization
Renderer based
OpenGL Renderers / Utilities
Basic Geometry
Skybox
Mesh Rendering
Geometry
Mesh
Primitives
Collision Detection (under construction)
Impulse Based Dynamics (under construction)
Other planned Dynamics algorithms
Force based
Parameterized Model (ABA/CRBA)
Simulation Model
Hub based model (every object may be announced across the whole simulation hierarchy)
Enhanced module based simulation (mybe visually compsible) (planned)
generic simulation model (still under construction)

Logging
Objectwise / Classwise / global
UnitTesting
My own reflectable Unit Testing framework has
Simple Tests
Templated Unit Tests
Performance Tests
GUI (planned)
Scripting
using reflection scripting will be enabled in future for
LUA (available)
Python (planned)
Javascript (planned)
Ruby (planned)
...
Reader
URDF Model workable but still under construction
Matlab file reader
obj reader
ply reader



## Serialization
Motivation
 Serialization is a central part for software systems that 
need to persist their state (save)
need to communicate with other systems
Using Reflection Serialization becomes a systematic and generally implementable task.  
First thoughts
I want a serialization framework which allows 
many different formats and is easy to use.
Classes should be allowed to be serialized by reflection but also by custom serialization
Serialization should be allowed to streams/files/strings etc. 
Types and formats should be inferred as far as possible for ease of use

via attributes and or methods (templated).
Example:
// serialization
 Color red(1,0,0);
 auto result = serialize(red,"json");
 CHECK_EQUAL("{'r':0, 'g':0, 'b':0}",result)

// deserialization
std::shared_ptr<Color> result = deserialize(result);
// color should be equal to red and format is inferred


##Uniform Property Definition
Version 5, last updated by Tobias Becker at 2013-02-01
 Uniform Property Definition
Abstract
Uniform Property Definition is what I call defining Properties by macros. I developed this "technique" to reduce coding overhead and to help with the implementation of my Reflection classes. 
Motivation
While implementing classes with a lot of properties I getting tired of writing code which felt very repetetive and redundant like the following:
class Person{
private:
    std::string _firstName;
    std::string _lastName;
public:
    std::string getFirstName()const{return _firstName;}
    void setFirstName(const std::string value){_firstName=value;}
    const std::string & firstName()const{return _firstName;}
    std::string & firstName(){return _firstName;}


    std::string getLastName()const{return _lastName;}
    void setLastName(const std::string value){_lastName=value;}

};
Obviously everthing repeats, like the Name of the property's getter and setter methods, the fieldname and the reference access method's name.  Also the datatype is used excrutiatingly much.  this is especially unnerving for me when the datatypes are long like std::map<std::string, std::map<std::string, std::vector<std::string>>> .

My wish was to only write information once like so:  
PROPERTY(std::string, FirstName)
First Iteration

The first Implementation, which is currently used widely in my project, follows a very structured build up of macros.  
See Members.h.  It is documented which is good, since the macros are nested pretty deeply.

Second Iteration
Motivation
I am not happy with the first Iteration.  The type information is still used too much, for every statement like the following:
... .h
PROPERTY(int,NumberVariable);
REFERENCES(int,NumberVariable);

... .cpp
void ClassName::propertyChanging(int, NumberVariable){

}



Also Macros do not take kindly to too many commas when passing argument, macros are after all just part of a "stupid" or I guess "simple" preprocessor language.
This causes problems when passing a type which includes commas; namely templated types with multiple template arguments :
std::map<std::string, std::string> 
A statement like the previous would destroy the macros...
Idea
Typedef the type once, and make it so that it is easy to write and read.
What I wanted:
std::map<std::string,std::string> PROPERTY(MyMapVariable);
which will also generate all the getter and setter code and fields.  Also I want to be able to specify the storage type:
std::map<std::string,std::string> PROPERTY(MyMapVariable STORAGE(REFERENCE));
std::map<std::string,std::string> PROPERTY(MyMapVariable STORAGE(CALLBACKS(mySetCallback, myGetCallback));
std::map<std::string,std::string> PROPERTY(MyMapVariable STORAGE(POINTER));
std::map<std::string,std::string> PROPERTY(MyMapVariable STORAGE(FIELD));

This was hard to do with the limited preprocessor capabilities.
You can see my first tries in reflection.cpp where I solved the type definition problem by using decltype and a unused static method.

Another simplification I wanted/needed was allowing access to the pointcuts when properties change/are retrieved.
Generally three events are only interesting as illustrated in pseudo code:

void setProperty(PropertyType value){
    // before property is set
    if(onBeforePropertySet(value))return;
    store property
    // after property is set 
    onAfterPropertySet(value);

}
PropertyType getProperty()const{
    onBeforePropertyGet();
    return retrieve property;
    // nothing can happen here
}
This would be relatively easy to write but I want it to be easy to use:
[...]//inside struct/class

int PROPERTY(MyProperty);


beforeGet(MyProperty){
    cout<< _MyProperty << endl;
}
beforeSet(MyProperty){
    cout << "MyProperty changing: "<<_MyProperty<<" -> "<< value<<endl;
}
afterSet(MyProperty){

}

A further constraint is that I want the compiler to optimize away all code that is not needed --> if beforeSet(...) is not defined i want the if() statement to be removed.
Also it has to be fast (optional virtual methods, everything inlineable) . 

I found a couple of nice approaches, all of which were not standard compatible because either they rely on __if_exists() (MSVC) which executes code only if a symbol is defined or
non-standard templating: specializing class template methods inside class.  

So my solution is based on an almost unspectacular technique:  method overloading.
To be continued...
Comments are disabled for this project. You can enable comments from the Wiki Settings page.



## Templated Integration Framework
Version 1, last updated by Tobias Becker at 2013-02-17
Templated Integration

Steppers:
Explicit Euler
Implicit Euler
Semi-Explicit Euler
Runge Kutta order 4
Runge Kutta order 2
Adams-Bashford 4
Adams-Moulton 4
...

Example:

Following simple example for an Explicit Euler stepper:
auto f = [](double x,double h,double t)->double{return t;};
//create explicit euler stepper (t0=0.0; x0=0.0, h0=0.02)
ExplicitEuler<decltype(f)> stepper(f);
// set timestep:
stepper.h()=0.001;
// step until t=1.0;
stepper.stepUntil(1.0);

cout << stepper.i()<<endl; //-> "1000"
cout << stepper.x() <<endl; // -> 0.49995 (error: 0.0005 < h()^1)
Comments are disabled for this project. You can enable comments from the Wiki Settings page.


## Reflection
Version 9, last updated by Tobias Becker at 2013-07-23
 C++ Reflection
Motivation
What I missed most while transitioning from C# to C++ was the reflection model for Classes and its members.  Especially in a simulation environment objects have many properties and methods, that the user might want to tweak with new values during runtime.  Writing a GUI / UI for these values is very tiresome and very repetitive. Also serializing Objects to store state or to transfer them to script languages would be a huge task if everything were written by hand.  This is were reflection unfolds its advantages.  When a object is reflectable (and annotable) the whole user interface can be generated by iterating over an object's properties.  
Another reason for some kind of reflection is type identification.  dynamic_casts are a bottleneck in realtime code were millions of elements have to be cast in seconds (like in collision detection). static casts are much preferred.  Virtual methods to determine type are "slow" compared to normal or inline class methods if called at the appropriate rate.  So I wanted/needed a type system which is performant in  identification and casting.  Ideally comparing two integers for checking type if a object is of the correct type is the optimal way to go.
There are already a couple of libraries that support reflection.  I wanted to learn  about reflection techniques myself (and keep total control of the source) and I wanted something simple at first therefore I wrote my own reflection library which I make use of extensively throughout this project.  
Other Implementations
A couple of implementations exist already for reflection.
Boost.Mirror 
XCppRefl
SWIG (needs an external build step to work)+
http://sourceforge.net/projects/cppreflect/ 
http://grid.cs.binghamton.edu/projects/publications/c++-HPC07/c++-HPC07.pdf
Objective
 In the following I will list what kind of features my reflection implementation should have|has.
Type system: Querying the type of a class 
Type Hierarchy - allows Child types access to parent properties
Properties (see also Uniform_Property_Definition
Pointers to other complex types
Simple properties to primitive types,
Propertysets for simple and complex types
Methods
simple Actions methods (void (void))
more complex methods...
Annotations/Attributes
For specifying GUI visualization
For serialization
For validation
...
Extensible by User
Usable independantly from my object Hierarchy (highly reusable classes)
Easy use.  Clients should only have to add minimal code to their own classes/types to use reflection 

Implementation
The basis for my reflection model is the Uniform_Property_Definition.
By extending the macros I use for defining properties without code overhead I could easily add the definitions needed for reflecting over the types and objects.
Type System
In my approach I define an Objects type as an unique Identification number. Basically I have a counter which is query by each class to generate a new id (increment last id by 1)
A class is used to store this id and the name of the type and its members.  Only one instance of this class may ever exist to prevent mixups.  The definition of this type can be found in: Type.h  
A Type has the following capabilities
a unique Id (uint)
a name (string)
a set of Member Objects (may by Properties, Methods, Actions)
a set of Attributes 
a create instance function which returns a pointer to an instance
a delete instance function.
Preceeding types and Child types
Since c++ allows multiple inheritance the Type is itself a Node of a graph.
All graph algorithms can be applied to the Type hierarchy

Types can be created for Objects (the base class for complex types in my library) but also for primitives (by specializing the Template class TypeInfo)

.. to be continued

Method Reflection
It is possble to enable reflection for any type of method.
Following Reflection information is available:
Name of Method
Return Type
Argument Types
is const flag
call method
Following shows how easily reflection is enabled for a method
struct A{
 // a macro which enables type reflection for a type. (see TypeInfo.h)
 reflect_type(A);

 //
 reflect_method(add);
 int add(int a, int b,std::string message)const;
};


// source
int A::add(int a, int b, std::string message)const{
    std::cout << message << (a+b) <<std::endl; 
    return a+b; 
}
With the declaration above one can easily reflect and also call the method dynamically:
...

A obj;
auto type = type_of(obj); // =type_of<A>();
auto methodInfo = type->getMethodInfo("add");
Argument args[2]={4,3,std::string("the result is: ")}; // create a container for arguments
auto result = methodInfo->call(&obj, args);
// following text was printed after call: "the result is: 7"
std::cout << (int)result<<std::endl; 
// the line above prints "7"


...
Constructor Reflection
To properly construct objects via scripts/ serialization without mandating the presence of a public default constructor I added constructor reflection

To enable reflection for a constructor one needs to do the following:
(Obsolete code - this has changed a bit)

...
struct TypeA{
    // declare type reflectable 
    reflect_type(TypeA);
    
    // declare a public constuctor with minimal overhead:
    // the name of the type needs to be known to this macro (this is dissapointing but there is no workaround for this)
    reflect_constructor(public: TypeA, int i, std::string str, double d){
        // print the arguments to stream.
        std::stringstream stream;
        stream << str<<i<<d;    
        result = stream.str();
    }    
    std::string result;
};
// instanciate TypeA somewhere to initialize reflection


...
// get type by reflection
auto type = typeof(TypeA);
// create argument list for construction
Argument args[3] = {3,std::string("hello"),3.14};

// create object instance
auto instance = type->construct(args);

std::cout << instance.cast<TypeA>()->result << std::endl;
// line above returns "hello33.14"


Property Reflection
Property reflection depends on method reflection.  A reflected property consists of up to three variables:
the name
the get method
the set method
To enable reflection for a getter and setter method refer to the following example:
struct X{
  // type needs to be reflectable.  
  reflect_type(X)
  // two methods for accessing a property their names are
  // arbitrary
  int aGetterMethod(){
    cout << "getting property";
    return 3;
  }
  void aSetterMethod(int newvalue){
    cout << "setting property to "<<newvalue;
  }
  //specify property called "IntTestProperty"
  //      /-----------   Macro for reflecting over property
  //      |             /-----------  Name of the property
  //      |             |               /-- the getter method
  //      |             |               |            / -- the setter method
  reflect_property(IntTestProperty,aGetterMethod,aSetterMethod);  
};
Accessing the property is also simple:
// 1.  get property info  (remember that an Instance of X has to be instanciated
auto info = typeof(X)->getProperty("IntTestProperty");
cout << info->getName()<<": "<<info->getPropertyType()->getName()<<endl;
// prints "IntTestProperty: int"
// 2. create an adapter for accessing property of an X instance
X x; // create instance 
auto value = PropertyAdapter(x,"IntTestProperty");
cout << (int)value; // prints "getting property 3"
value = 33; // prints "setting property to 33"


Adding reflection without modifying existing code

If you need to reflect something without changing the original code( like libraries from someone else, or without wanting the constraint that in class reflection needs one instanciation for it to be set up ) you can do that also.
All you need is a source file (which is compiled - if a sourcefile exists without anyone referencing anything defined in it it will not be compiled by msvc at least).  Then you can start using the builder system.


namespace namespace1{
struct X{
  X(){}
  std::string method1(){return "1";}
  std::string method2(){return "2"}
  // overloaded methods
  std::string overloadedMethod(int i){stringstream stream; stream << i ; return stream.str();}
  std::string overloadedMethod(int i)const{...}
  static  std::string overloadedMethod(int i, int j){}
  int overloadedMethod(std::string s){...}
  //fields
  int _value1;
  //property
  int getValue1(){return _value1;}
  void setValue1(int val)const{_value=val;}
};
}

// in a source file somewhere : 
using namespace1
reflect<X>()
 ->name("::namespace1::X")
 // reflect simple method
 ->method(X::method1)
  ->name("method1")
  ->attribute(make_shared<MyAttribute>("this is an attribute for method 1")
  ->end()
 //reflect overloaded method (using signature identification functions)
 ->method(const_signature(overloadedMethod)
->end()
 ->end()

reflect_begin(namespace1::X)
 _default_constructor(X);
 _methods(method1,method2);
 _property(Value1,getValue1,setValue1)
reflect_end

reflecting private members (static reflection method)


... to be continued



## Types
Version 2, last updated by Tobias Becker at 2013-06-24
 Motivation
Types are the basis of most languages. And types come in all shapes and sizes.  The type system needs to be very flexible to handle different modi of reflecting over types. Types may be reflected inline, or uninvasively (in a separate file) possibly even in a separate assembly.  (when reflecting a library which you have only headers for.

Intuition
The first step is to define a type class which models the c++ programming model as good as possible. This includes
Classes, Structs, primitives
templated classes/structs
template arguments
boxed classes
modifiers, (const, pointers, references)
... 
To reflect types I heavily rely on templating.  Especially template specialization allows me to reflect types which do not belong to my code base ie 3rd party libraries
Reflection has to be as easy as possible so many macros need to be created to allow short and concise reflection statements

How


Comments are disabled for this project. You can enable comments from the Wiki Settings page.



## Namespaces and Scopes
Version 2, last updated by Tobias Becker at 2013-06-24
Motivation
If your create a large application you should probably use namespaces to separate your classes which allows for shorter classnames and bounds cluttering.  For reflection this also needs to be implemented.  Especially because the normal way to search for a reflected type which is unknown at compile time via its fully qualified name.
Intuition 
 To model Namespaces and Scopes in C++ I added the ScopeInfo and NamespaceInfo classes.  Currently they are almost synonyms because NamespaceInfo just inherits ScopeInfo.  The distinction is that scopes could also be classes, methods, etc while namespaces are just namespaces.  

Because reflection is supposed to be easy to use I choose not to enforce strict naming (specifying namespaces for all reflected types) .  

How?
When reflecting a type via reflect_type you should pass the fully qualified name of the type e.g. ::int or ::std::istream. This allows the classes to figure out into which namespace the type is to be placed.  If you choose not to pass the fully qualified name the type will be placed into the namespace ::default.  Most simple applications can decide might decide not to use namespaces.  This is anticipated and allowed.  

If you want to search for a type by name you need to access the Global namespace. You can see it in action in the following snippet  

// access global namespace and search for string type.  Then create an instance and cast it to actually be usable.
auto globalNamespace = NamespaceInfo::Global();
auto stringType = globalNamespace->find("std::string");
// construct via default constructor  (this may seem obvious: the type needs to be default constructible or an error occurs)
auto reflectedString = stringType->new();
std::shared_ptr<std::string> actualString = reflectedString;



Comments are disabled for this project. You can enable comments from the Wiki Settings page.



## Scripting
Version 5, last updated by Tobias Becker at 2013-03-09
Introduction
 Scripting is a very useful feature, especially for the beginner. When playing around a scripting language makes everything so much more easy. Also scripting is a great tool in all kinds of areas in a large application. Especially needing not to recompile nor to use the c++ debugger enhances productivity.
So of course I decided to implement a scrtipting interface.  Thanks to the Reflection library adding script support is very "easy" at least conceptiually.
One could say I am a abstraction fetishist (which actually is a quite bad quality) so the goal is to allow any scripting language with the fullest library support possible.
I want to connect at least the following languages 
Lua
JavaScript
Python

Scripting Interface
The Scripting Interface is kept as simple as possible.  The following bullets summarize what functionality is expected:
Object Access
properties
methods
construction
adding C++ objects to script from C++ side
creating C++ objects in script and serving them to the C++ application
calling script functions 
calling C functions/lambdas
set script variable
get script variable
getting complex script types

Memory Management
One notices quickly that scripting can cause memory leaks easily. So from the start I will use smart pointers as much as possible (actually only).

Languages
Lua
My choice for the first scripting language is Lua.  Lua is simple to learn, simple to use and easy to connect to c++ ( at least in marketing). Also the documentation is great.  A lot of C++ applications have Lua support ( the only one that I can remember off the bat is WoW ;) ).  Another and reason for me to connect Lua is that I have never done it before (in contrast to javascript)

Lua embedding is still under construction.
JavaScript
Python
My Python scripting is documented by the corresponding UnitTests.  You can see the possibilities of Python scripting there. However in the following are three examples of using scripting with C++.  

Python support is now complete (only getting complex types does not yet work.
Example 1
// Example 1
#include <scripting.python.h>
#include <string>
#include <sstream>
#include <iostream>

struct TestType{
 reflect_type(TestType);
 reflect_method(method1)
 string method1(int i, std::string n){
   stringstream stream;
   stream << i << ". " << n;
 }
};
int main(){
 PythonScriptMachine machine;
 TestType instance;
 machine.setVariable("var1", instance);
 machine.loadString(
  "print(var1.method1(44, ' Sendung'))\n"
  "var2 = var1.method1(33, '32')"
 )
 string result = machine.getVariable("var2");
 cout << result<<endl;
}

Result 1
44. Sendung       <-- from python print function
33.32             <-- from std:cout

Example 2
#include <scripting.python.h>
int main(){
  PythonScriptMachine machine;
  machine.loadString(
   "def fuu(i,j,k):\n"
   "  return i*j*k\n"
  )
  auto f  machine.getFunction("fuu");
  std::cout << (int) f(3,2,1) std::endl;  
}
Result 2
6

Example 3
#include <scripting.python.h>
using namespace std;
using namespace ds;
int main(){
    PythonScriptMachine machine;
    machine.setFunctor("testFuu", [](int i, string str){cout << i << " " <<str<<endl;});
    machine.loadString("testFuu(32,'hello')");
    
}
Result:
32 hello


##Unit Testing
Version 5, last updated by Tobias Becker at 2013-02-17
 Motivation
This motivation section is relatively short: Unit Tests are useful and save time.
Approach
When starting to write the math library I noticed that programming without unit tests will not work.  I wanted a lightweight Unittesting framework to quickly write tests.  Being spoiled from C# (where I could use VS testing and nCrunch for live unit testing) I was dissapointed that Unittesting in C++ seemed so hard.  
A quick internet search resulted in me finding CppUnitLight and alas I started writing CppUnitLight tests. After a while I noticed that I needed/ wanted more functionality. 
Test Types
Basic Unit Tests
I implemented my own unit testing framework (with the same Syntax as CppUnitLight so that I did not need to rewrite tests written up to the point in time)

The basic unit tests have following Properties:
class UnitTest
toString -> writes the result of the test to string
FailedTests -> number of checks which failed (should be renamed to FailedChecks)
TestStartTime -> stores beginning of execution
TestEndTime -> stores end of execution
Time -> stores the time it took to execute test (should be rather called duration)
TestName -> stores name of the test
TestDescription -> stores a description of the test
Info -> stores source info about the test (Line, File, Compiler, function etc)
Results -> stores info about every check performed in a test (if all checks succeeded the test was successful)

Example:
//declare a Unit Test (CppUnitLight style)
TEST(1, TestName){
    CHECK_EQUAL(2,2); //passes
    CHECK(true); // passes
    DOUBLES_EQUAL(1.0001,1,0.001);// passes
    CHECK_TYPES(int,int); //passes
    FAIL("message") //fails
}
// declare a Unit Test (ds style)
UNITTEST(TestName){
    // [...] 
}
I extended the functionality by a more complex and reflectable testrunner which allows execution of single tests, manual test registration, etc. so a GUI can later be used to run it.
Templated Unit Tests
I added templated tests which allow Tests to use template arguments and can be instanciated multiple times for different type by a one liner.
** Note: the test syntax has changed but is very similar
Example:
//declare a test with two template arguments
template<typename T1, typename T2>
TTEST(TestName){
    // this test checks wether the two types are the same (It is really not a very usefull test)
    bool sameType= std::is_same<T1,T2>::value
    CHECK(!sameType);
}
// now instanciate the test for different types
TTEST_INSTANCE(TestName, int, int); //-> will fail because typeof(int)==typeof(int)
TTEST_INSTANCE(TestName, std::string, int);//->will succeed
TTEST_INSTANCE(TestName, std::string, std::string);//-> will succeed
Performance Unit Tests
Besides templated tests I am also interested in the performance of code produced so I created a PerformanceTest class (which is designed to have no overhead and measure the time as precise as possible.  I plan to extend it so I can compare performance with previous design iterations so one has an insight in performance improvements.   Furthermore I want to be able to add a reference implementation for performance tests (same as with precision tests) so I can check the overhead of tested code.
Note: The test itself should not take too long (less than a second), maybe I will create another test type for testing longer performance sensitive code - up to now I do not see the need.
Example:
PTEST(TestName){
    // define unit under test
    static MatrixNxM a(100,100);
    static MatrixNxM b(100,100);
    // test operation (matrix multiply)
    auto c = a*b;
}
Printing the test above will result in following:
Performance test 'TestName' duration: 0.005145s; 203 iterations executed in 1.044488s; # of primer iterations: 4
Precision Unit Tests
to be continued.
Comments are disabled for this project. You can enable comments from the Wiki Settings page.
