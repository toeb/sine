template<typename C,typename A,typename OP>
  class MatrixElementWiseUnary{
  public:
    static inline void operation(C & c, const A &  a){      
      c.resize(a.rows(),a.cols(),false);
      for(int i=0; i < a.rows(); i++){
        for(int j=0; j < a.cols(); j++){
          OP::operation(c(i,j), a(i,j));
        }
      }
    }
  };
  
  