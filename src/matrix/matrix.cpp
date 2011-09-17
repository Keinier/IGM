
#include <IEMath\matrix\matrix.h>




//////////////////////////////////////////////////////////////////////////////
// Matriz 3x3
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
const Matrix33<TReal> Matrix33<TReal>::ZERO=Matrix33<TReal>(0,0,0,0,0,0,0,0,0);
template<typename TReal>
const Matrix33<TReal> Matrix33<TReal>::IDENTITY;

//////////////////////////////////////////////////////////////////////////////
// Matriz 4x4
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
const Matrix44<TReal> Matrix44<TReal>::ZERO=Matrix44<TReal>(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
template<typename TReal>
const Matrix44<TReal> Matrix44<TReal>::IDENTITY;


