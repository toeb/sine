#pragma once
#include <math.functions.h>
#include <core.h>
#include <string>
#include <core.logging.h>
namespace nspace{
  /*
  template<typename T, uint Format=0>
  class FormatSerializer : public Serializer<T>{
  public:
    static bool serialize(std::ostream & stream, const T & value);
  };
  template<typename T, uint Format=0>
  class FormatDeserializer : public Serializer<T>{
  public:
    static bool deserialize(T& value, std::ostream & stream);
  };


  template<>
  class FormatSerializer<PiecewiseFunction<VectorND>, 0>{
  public:
    static bool serialize(std::ostream & stream,const PiecewiseFunction<VectorND> & value){

    }

  };*/


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