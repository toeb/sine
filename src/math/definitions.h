#pragma once

#if 1
#include <math/types/StaticMatrix.h>
#include <math/types/MatrixNxM.h>
#include <math/types/Matrix3x3.h>
#include <math/types/Quaternion.h>
#include <math/types/Vector3D.h>
#include <math/types/Matrix4x4.h>
#include <math/types/VectorND.h>
#include <math/types/Matrix4x3.h>
#include <math/types/Vector2D.h>
#include <math/MatrixOperations.h>
//#include <math/types/Vector4D.h>
//#include <math/types/Matrix4x3.h>
//#include <math/types/Matrix3x4.h>
#else

typedef int MatrixNxM;
typedef int Matrix3x3;
typedef int Quaternion;
typedef int Vector3D;
typedef int Matrix4x4;
typedef int VectorND;
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif