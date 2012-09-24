#include <config.h>

namespace nspace{

template<typename TargetType>
class MatrixResize{
public:
static inline void operation(TargetType  & target, uint rows, uint cols, bool setToZero){
 target.resize(rows,cols);
 if(setToZero) MatrixSetConstant<Real,TargetType>::operation(target,0.0);
}
};

}
