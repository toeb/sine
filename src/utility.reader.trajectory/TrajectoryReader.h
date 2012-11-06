#pragma once
#include <math.functions.h>
#include <core.h>
#include <string>
#include <core.logging.h>
namespace nspace{
  //TODO Implement cubic reader
class TrajectoryReader : public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(TrajectoryReader);
  SUBCLASSOF(Log);

  PROPERTYSET( PiecewiseFunction<VectorND>*, Trajectories,{},{});
  PROPERTY( PiecewiseFunction<VectorND>*, LastTrajectory){Trajectories().add(newvalue);};
public:
  // reads a trajectory.  the format of the stream must be as used in DirCol
  bool read(std::istream & stream, PiecewiseFunction<VectorND>** trajectory=0);
private:

  bool parseCubicPiecewiseFunction(PiecewiseFunction<VectorND> * piecewise, std::vector<double> & doubles, int dim);
  bool parseLinearPiecewiseFunction(PiecewiseFunction<VectorND> * piecewise, std::vector<double> & doubles, int dim);

};
}