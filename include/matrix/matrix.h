/********************************************************************************	
 *   Copyright (C) 2011  Keinier Caboverde R.									*
 *																				*	
 *  This program is free software: you can redistribute it and/or modify		*
 *   it under the terms of the GNU General Public License as published by		*
 *   the Free Software Foundation, either version 3 of the License, or			*
 *   (at your option) any later version.										*
 *																				*
 *   This program is distributed in the hope that it will be useful,			*
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of				*
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				*
 *   GNU General Public License for more details.								*
 *																				*
 *   You should have received a copy of the GNU General Public License			*
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.		*
 *																				*
 *******************************************************************************/
#ifndef _MATRIX_H
#define _MATRIX_H

#include <IEMath\vector\vector.h>

#include <cmath>
#include <assert.h>
#include <istream>



template<typename TReal>
struct Vector3D;

//////////////////////////////////////////////////////////////////////////////
/// \struct  Matrix33
/// \brief   Matriz 3x3
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
struct Matrix33
{
  union
  {
    struct
    {
      TReal m00, m01, m02,
      m10, m11, m12,
      m20, m21, m22;
    };
    struct 
    {
      TReal row0[3], row1[3], row2[3];
    };
    TReal ij[3][3];
    TReal e[9];
  };

  /// Ctor
  Matrix33()
	  {
  identity();
}

  Matrix33(TReal _m00, TReal _m01, TReal _m02,
    TReal _m10, TReal _m11, TReal _m12,
    TReal _m20, TReal _m21, TReal _m22)
	{
  m00 = _m00; m01 = _m01; m02 = _m02;
  m10 = _m10; m11 = _m11; m12 = _m12;
  m20 = _m20; m21 = _m21; m22 = _m22;
}

  Matrix33(TReal *m)
	  {
  assert(m != NULL);

  memcpy(e, &m[0], 9 * sizeof(TReal));
}

  Matrix33(const Vector3D<TReal> &_row0, const Vector3D<TReal> &_row1, const Vector3D<TReal> &_row2)
	  {
  memcpy(row0, _row0.v, sizeof(TReal) * 3);
  memcpy(row1, _row1.v, sizeof(TReal) * 3);
  memcpy(row2, _row2.v, sizeof(TReal) * 3);
}
  Matrix33(const Matrix33<TReal> &m)
	  {
  memcpy(e, m.e, 9 * sizeof(TReal));
}

  /// Asignacion
  Matrix33<TReal> &set(TReal _m00, TReal _m01, TReal _m02,
    TReal _m10, TReal _m11, TReal _m12,
    TReal _m20, TReal _m21, TReal _m22)
	{
  m00 = _m00; m01 = _m01; m02 = _m02;
  m10 = _m10; m11 = _m11; m12 = _m12;
  m20 = _m20; m21 = _m21; m22 = _m22;

  return (*this);
}

  Matrix33<TReal> &set(TReal *m)
	  {
  assert(m != NULL);
  memcpy(e, &m[0], 9 * sizeof(TReal));
  return (*this);
}
  Matrix33<TReal> &set(const Matrix33<TReal> &m)
	  {
  memcpy(e, &m.e, 9 * sizeof(TReal));
  return (*this);
}
  Matrix33<TReal> &setRows(const Vector3D<TReal> &_row0, const Vector3D<TReal> &_row1, const Vector3D<TReal> &_row2)
	  {
  memcpy(row0, _row0.v, sizeof(TReal) * 3);
  memcpy(row1, _row1.v, sizeof(TReal) * 3);
  memcpy(row2, _row2.v, sizeof(TReal) * 3);

  return (*this);
}
  
  Matrix33<TReal> &setColumns(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2)
	  {
  m00 = c0.x; m01 = c1.x; m02 = c2.x;
  m10 = c0.y; m11 = c1.y; m12 = c2.y;
  m20 = c0.z; m21 = c1.z; m22 = c2.z;

  return (*this);
}

  Matrix33<TReal> &operator=(const Matrix33<TReal> &m)
	  {
  memcpy(e, m.e, 9 * sizeof(TReal));

  return (*this);
}

  Matrix33<TReal> &operator=(const TReal *m)
	  {
  memcpy(e, &m[0], 9 * sizeof(TReal));

  return (*this);
}

  Matrix33<TReal> &identity()                             /// Transforma en matriz identidad
  {
  return Matrix33<TReal>(1, 0, 0, 0, 1, 0, 0, 0, 1);

 // return (*this);
}
  
  Matrix33<TReal> &clear()                                /// Todo a 0
{
  memset(e, 0, 9 * sizeof(TReal));

  return (*this);
}

  /// Operadores
  TReal* operator[] (int row) const
	  {
  assert(row < 3);

  return (TReal*)&ij[row][0];
}

  bool operator== (const Matrix33<TReal> &m) const
	  {
  for (int row = 0; row < 3; row++)
  {
    for (int col = 0; col < 3; col++)
    {
      if (ij[row][col] != m[row][col])
        return false;
    }
  }

  return true;
}
  bool operator!= (const Matrix33<TReal> &m) const
	  {
  return !operator == (m);
}

  Matrix33<TReal> operator - () const
	  {
  Matrix33<TReal> inv;
  
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      inv[row][col] = -ij[row][col];

  return inv;
}
  Matrix33<TReal> operator + (const Matrix33<TReal> &m) const
	  {
  Matrix33 sum;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      sum[row][col] = ij[row][col] + m[row][col];

  return sum;
}
  Matrix33<TReal> operator - (const Matrix33<TReal> &m) const
	  {
  Matrix33<TReal> diff;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      diff[row][col] = ij[row][col] - m[row][col];

  return diff;
}
  Matrix33<TReal> operator * (const Matrix33<TReal> &m) const
	  {
  Matrix33<TReal> prod;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      prod[row][col] = ij[row][0]*m[0][col] + ij[row][1]*m[1][col] + ij[row][2]*m[2][col];

  return prod;
}
  Matrix33<TReal> operator * (TReal scalar) const
	  {
  Matrix33<TReal> prod;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      prod[row][col] = scalar*ij[row][col];

  return prod;
}

  /// Operaciones
  Matrix33<TReal> transpose() const                       /// Transpuesta
	  {
  Matrix33<TReal> trans;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      trans[row][col] = ij[col][row];

  return trans;
}
  Matrix33<TReal> inverse() const                         /// Inversa
	  {
  Matrix33<TReal> inverse;

  inverse[0][0] = ij[1][1]*ij[2][2] - ij[1][2]*ij[2][1];
  inverse[0][1] = ij[0][2]*ij[2][1] - ij[0][1]*ij[2][2];
  inverse[0][2] = ij[0][1]*ij[1][2] - ij[0][2]*ij[1][1];
  inverse[1][0] = ij[1][2]*ij[2][0] - ij[1][0]*ij[2][2];
  inverse[1][1] = ij[0][0]*ij[2][2] - ij[0][2]*ij[2][0];
  inverse[1][2] = ij[0][2]*ij[1][0] - ij[0][0]*ij[1][2];
  inverse[2][0] = ij[1][0]*ij[2][1] - ij[1][1]*ij[2][0];
  inverse[2][1] = ij[0][1]*ij[2][0] - ij[0][0]*ij[2][1];
  inverse[2][2] = ij[0][0]*ij[1][1] - ij[0][1]*ij[1][0];

  TReal det = ij[0][0]*inverse[0][0] + ij[0][1]*inverse[1][0] + ij[0][2]*inverse[2][0];

  TReal inv = 1.0f / det;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      inverse[row][col] *= inv;

  return inverse;
}
  TReal determinant() const                     /// Determinante
	  {
  TReal factor00 = ij[1][1]*ij[2][2] - ij[1][2]*ij[2][1];
  TReal factor10 = ij[1][2]*ij[2][0] - ij[1][0]*ij[2][2];
  TReal factor20 = ij[1][0]*ij[2][1] - ij[1][1]*ij[2][0];

  TReal det = ij[0][0]*factor00 + ij[0][1]*factor10 + ij[0][2]*factor20;

  return det;
}
  static Matrix33<TReal> transpose(Matrix33<TReal> &m)
	  {
  Matrix33<TReal> trans;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      trans[row][col] = m.ij[col][row];

  m.set(trans);

  return m;
}
  static Matrix33<TReal> inverse(Matrix33<TReal> &m)
	  {
  Matrix33<TReal> inverse;

  inverse[0][0] = m.ij[1][1]*m.ij[2][2] - m.ij[1][2]*m.ij[2][1];
  inverse[0][1] = m.ij[0][2]*m.ij[2][1] - m.ij[0][1]*m.ij[2][2];
  inverse[0][2] = m.ij[0][1]*m.ij[1][2] - m.ij[0][2]*m.ij[1][1];
  inverse[1][0] = m.ij[1][2]*m.ij[2][0] - m.ij[1][0]*m.ij[2][2];
  inverse[1][1] = m.ij[0][0]*m.ij[2][2] - m.ij[0][2]*m.ij[2][0];
  inverse[1][2] = m.ij[0][2]*m.ij[1][0] - m.ij[0][0]*m.ij[1][2];
  inverse[2][0] = m.ij[1][0]*m.ij[2][1] - m.ij[1][1]*m.ij[2][0];
  inverse[2][1] = m.ij[0][1]*m.ij[2][0] - m.ij[0][0]*m.ij[2][1];
  inverse[2][2] = m.ij[0][0]*m.ij[1][1] - m.ij[0][1]*m.ij[1][0];

  TReal det = m.ij[0][0]*inverse[0][0] + m.ij[0][1]*inverse[1][0] + m.ij[0][2]*inverse[2][0];

  TReal inv = 1.0f / det;

  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      inverse[row][col] *= inv;

  m.set(inverse);

  return m;
}

  /// Logs
  friend __declspec(dllimport) std::ostream &operator<< (std::ostream &o, const Matrix33<TReal> &m)
	  { 
  o << "Matrix33(" << m.m00 << ", " << m.m01 << ", " << m.m02 <<
                  m.m10 << ", " << m.m11 << ", " << m.m12 <<
                  m.m20 << ", " << m.m21 << ", " << m.m22 << ")";

  return o;
}
  /// Matrices especiales
  static const Matrix33<TReal> ZERO;
  static const Matrix33<TReal> IDENTITY;
};


//////////////////////////////////////////////////////////////////////////////
/// \struct  Matrix33
/// \brief   Matriz 4x4
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
struct Matrix44
{
  union
  {
    struct
    {
      TReal m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33;
    };
    struct 
    {
      TReal row0[4], row1[4], row2[4], row3[4];
    };
	
    TReal ij[4][4];
    TReal e[16];
  };

  /// CTor
  Matrix44()
	  {

  identity();

}
  Matrix44(TReal _m00, TReal _m01, TReal _m02, TReal _m03,
    TReal _m10, TReal _m11, TReal _m12, TReal _m13,
    TReal _m20, TReal _m21, TReal _m22, TReal _m23,
    TReal _m30, TReal _m31, TReal _m32, TReal _m33)
	{
  m00 = _m00; m01 = _m01; m02 = _m02; m03 = _m03;
  m10 = _m10; m11 = _m11; m12 = _m12; m13 = _m13;
  m20 = _m20; m21 = _m21; m22 = _m22; m23 = _m23;
  m30 = _m30; m31 = _m31; m32 = _m32; m33 = _m33;
}

  Matrix44(TReal *m)
	  {
  assert(m != NULL);

  memcpy(e, &m[0], 16 * sizeof(TReal));
}

  Matrix44(const Vector3D<TReal> &_row0, const Vector3D<TReal> &_row1, const Vector3D<TReal> &_row2)
	  {
  memcpy(row0, _row0.v, sizeof(TReal) * 3);
  memcpy(row1, _row1.v, sizeof(TReal) * 3);
  memcpy(row2, _row2.v, sizeof(TReal) * 3);
  memset(row3, 0, sizeof(TReal) * 3);
  ij[3][0] = ij[3][1] = ij[3][2] = 0.0;
  ij[3][3] = 1.0;
}

  Matrix44(const Vector3D<TReal> &_row0, const Vector3D<TReal> &_row1, const Vector3D<TReal> &_row2, const Vector3D<TReal> &_row3)
	  {
  memcpy(row0, _row0.v, sizeof(TReal) * 3);
  memcpy(row1, _row1.v, sizeof(TReal) * 3);
  memcpy(row2, _row2.v, sizeof(TReal) * 3);
  memcpy(row3, _row3.v, sizeof(TReal) * 3);
  ij[3][0] = ij[3][1] = ij[3][2] = 0.0;
  ij[3][3] = 1.0;
}
  Matrix44(const Matrix44<TReal> &m)
	  {
  memcpy(e, m.e, 16 * sizeof(TReal));
}

  /// Asignacion
  Matrix44<TReal> &set(TReal _m00, TReal _m01, TReal _m02, TReal _m03,
    TReal _m10, TReal _m11, TReal _m12, TReal _m13,
    TReal _m20, TReal _m21, TReal _m22, TReal _m23,
    TReal _m30, TReal _m31, TReal _m32, TReal _m33)
	{
	m00 = _m00; m01 = _m01; m02 = _m02; m03 = _m03;
  m10 = _m10; m11 = _m11; m12 = _m12; m13 = _m13;
  m20 = _m20; m21 = _m21; m22 = _m22; m23 = _m23;
  m30 = _m30; m31 = _m31; m32 = _m32; m33 = _m33;

  return (*this);
}

  Matrix44<TReal> &set(TReal *m)
	  {
  memcpy(e, m, 16 * sizeof(TReal));

  return (*this);
}


  Matrix44<TReal> &set(const Matrix44<TReal> &m)
	  {
  memcpy(e, &m.e, 16 * sizeof(TReal));

  return (*this);
}

  Matrix44<TReal> &setRows(const Vector3D<TReal> &_row0, const Vector3D<TReal> &_row1, const Vector3D<TReal> &_row2)
	  {
  memcpy(row0, _row0.v, sizeof(TReal) * 3);
  memcpy(row1, _row1.v, sizeof(TReal) * 3);
  memcpy(row2, _row2.v, sizeof(TReal) * 3);
  m03 = m13 = m23 = m33 = 0.0; m33 = 1.0;

  return (*this);
}
  
  Matrix44<TReal> &setColumns(const Vector3D<TReal> &c0, const Vector3D<TReal> &c1, const Vector3D<TReal> &c2)
	  {
  m00 = c0.x; m01 = c1.x; m02 = c2.x; m03 = 0.0;
  m10 = c0.y; m11 = c1.y; m12 = c2.y; m13 = 0.0;
  m20 = c0.z; m21 = c1.z; m22 = c2.z; m23 = 0.0;
  m30 = m31 = m32 = 0.0; m33 = 1.0;

  return (*this);
}

  Matrix44<TReal> &operator = (const Matrix44<TReal> &m)
	  {
  memcpy(row0, m.row0, sizeof(TReal) * 3);
  memcpy(row1, m.row1, sizeof(TReal) * 3);
  memcpy(row2, m.row2, sizeof(TReal) * 3);

  return (*this);
}

  Matrix44<TReal> &operator = (const TReal *m)
	  {
  memcpy(e, m, 16 * sizeof(TReal));

  return (*this);
}

  Matrix44<TReal> &identity()
	  {
  //memcpy(e, Matrix44<TReal>::IDENTITY.e, 16 * sizeof(TReal));
  return Matrix44<TReal>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  //return (*this);
}
  Matrix44<TReal> &clear()
	  {
	memset(e, 0, sizeof(TReal) * 16);

  return (*this);
}


  /// Operadores

  TReal* operator [] (int row) const
	  {
  assert(row < 4);

  return (TReal*)&ij[row][0];
}

  bool operator == (const Matrix44<TReal> &m) const
	  {
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++)
    {
      if (ij[row][col] != m[row][col])
        return false;
    }
  }

  return true;
}
  bool operator != (const Matrix44<TReal> &m) const
	  {
  return !operator == (m);
}

  Matrix44 operator - () const
	  {
  Matrix44 inv;
  
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      inv[row][col] = -ij[row][col];

  return inv;
}
  Matrix44 operator + (const Matrix44<TReal> &m) const
	  {
  Matrix44 sum;

  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      sum[row][col] = ij[row][col] + m[row][col];

  return sum;
}
  Matrix44 operator - (const Matrix44<TReal> &m) const
	  {
  Matrix44 diff;

  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      diff[row][col] = ij[row][col] - m[row][col];

  return diff;
}
  Matrix44 operator * (const Matrix44<TReal> &m) const
	  {
  Matrix44 prod;

  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      prod[row][col] = ij[row][0]*m[0][col] + ij[row][1]*m[1][col] + ij[row][2]*m[2][col] + ij[row][3]*m[3][col];

  return prod;
}
  Vector3D operator * (const Vector3D<TReal> &v) const
	  {
  Vector3D r;

  r.x = ij[0][0] * v.x + ij[0][1] * v.y + ij[0][2] * v.z + ij[0][3];
  r.y = ij[1][0] * v.x + ij[1][1] * v.y + ij[1][2] * v.z + ij[1][3];
  r.z = ij[2][0] * v.x + ij[2][1] * v.y + ij[2][2] * v.z + ij[2][3];

  return r;
}

  Matrix44<TReal> &operator *= (const Matrix44<TReal> &m)
	  {
  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      ij[row][col] = ij[row][0]*m[0][col] + ij[row][1]*m[1][col] + ij[row][2]*m[2][col] + ij[row][3]*m[3][col];

  return (*this);
}

  /// Operaciones
  Matrix44 transpose() const                       /// Transpuesta
	  {
  Matrix44 trans;

  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      trans[row][col] = ij[col][row];

  return trans;
}
  void rotateX(TReal fRads)
	  {
    m11 =  (TReal)IEMath<TReal>::Cos(fRads);
	m12 =  (TReal)IEMath<TReal>::Sin(fRads);
	m21 = -(TReal)IEMath<TReal>::Sin(fRads);
	m22 =  (TReal)IEMath<TReal>::Cos(fRads);
}
  void rotateY(TReal fRads)
	  {
	m00 =  (TReal)IEMath<TReal>::Cos(fRads);
	m02 = -(TReal)IEMath<TReal>::Sin(fRads);
	m20 =  (TReal)IEMath<TReal>::Sin(fRads);
	m22 =  (TReal)IEMath<TReal>::Cos(fRads);
}
  void rotateZ(TReal fRads)
	  {
	m00 =  (TReal)IEMath<TReal>::Cos(fRads);
	m10 =  (TReal)IEMath<TReal>::Sin(fRads);
	m01 = -(TReal)IEMath<TReal>::Sin(fRads);
	m11 =  (TReal)IEMath<TReal>::Cos(fRads);
}
  static Matrix44 transpose(Matrix44<TReal> &m)
	  {
  Matrix44 trans;

  for (int row = 0; row < 4; row++)
    for (int col = 0; col < 4; col++)
      trans[row][col] = m.ij[col][row];

  m.set(trans);

  return m;
}

  Matrix44 getCameraLookAt(Vector3D<TReal> &vFrom, Vector3D<TReal> &vAt)
	  {
	Vector3D vView = vAt - vFrom;
	vView.normalize();
	
  Vector3D vWorldUp = Vector3D::Y;
	TReal dotProduct = vWorldUp.dot(vView);
  Vector3D vUp = vWorldUp - (vView * dotProduct);

  vUp.normalize();

	Vector3D vRight = vView.cross(vUp);

	Matrix44 mat;
	mat.identity();

	mat.m00 = vRight.x; mat.m01 = vUp.x; mat.m02 = vView.x;
	mat.m10 = vRight.y; mat.m11 = vUp.y; mat.m12 = vView.y;
	mat.m20 = vRight.z; mat.m21 = vUp.z; mat.m22 = vView.z;

	mat.m30 = -(vFrom.dot(vRight));
	mat.m31 = -(vFrom.dot(vUp));
	mat.m32 = -(vFrom.dot(vView));

	return mat;
}
  Matrix44 getObjectLookat(Vector3D<TReal> &vFrom, Vector3D<TReal> &vAt)
	  {
	Vector3D vView = vAt - vFrom;
	TReal Length = vView.len();
	vView /= Length;

  Vector3D vWorldUp = Vector3D::Y;
	TReal dotProduct = vWorldUp.dot(vView);
	Vector3D vUp = vWorldUp - (vView * dotProduct);
	vUp.normalize();

	Vector3D vRight = vView.cross(vUp);

	Matrix44 mat;
	mat.identity();

	mat.m00 = vRight.x; mat.m10 = vUp.x; mat.m20 = vView.x;
	mat.m01 = vRight.y; mat.m11 = vUp.y; mat.m21 = vView.y;
	mat.m02 = vRight.z; mat.m12 = vUp.z; mat.m22 = vView.z;

	mat.m30 = vFrom.x;
	mat.m31 = vFrom.y;
	mat.m32 = vFrom.z;

	return mat;
}

  /// Logs
  friend __declspec(dllimport) std::ostream &operator<< (std::ostream &o, const Matrix44<TReal> &m)
	  { 
  o << "Matrix44(" << m.m00 << ", " << m.m01 << ", " << m.m02 << ", " << m.m03 << ", " <<
                  m.m10 << ", " << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " <<
                  m.m20 << ", " << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " <<
                  m.m30 << ", " << m.m31 << ", " << m.m32 << ", " << m.m33 << ")";

  return o;
}
  /// Matrices especiales
  static const Matrix44 ZERO;
  static const Matrix44 IDENTITY;
};



#endif // _MATRIX_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End Of File
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
