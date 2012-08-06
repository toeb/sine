template<typename T>
class ScalarOperations{
public:
  static inline void Zero(T & element){element =0;}
  static inline void Identity(T& element){element =1;}
  static inline void add(T & sum, const T &a, const T &b){
    sum = a+b;
  }
  static inline void subtract(T & difference, const T & a, const T &b){
    difference = a-b;
  }
  static inline void negate(T & b, const T& a){
    b = -a;
  }
  static inline void multiply(T &c, const T & a, const T & b){
    c = a*b;
  }
  static inline void divide(T & c, const T &a, const T &b ){
    c = a / b;
  }
  static inline void sqrt(T & b, const T& a){
    b = std::sqrt(a);
  }
  static inline void abs(T & result, const T & a){
    result = std::abs(a);
  }

  static inline void reciprocal(const T a, T & b){
    divide(unitElement, a,b);
  }
};