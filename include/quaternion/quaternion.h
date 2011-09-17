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
#ifndef _QUAT_H
#define _QUAT_H

#include <istream>
#include <IEMath\core\iemath_core.hpp>
#include <IEMath\vector\vector.h>
#include <IEMath\matrix\matrix.h>

template<typename TReal>
struct Vector3D;
template<typename TReal>
struct Matrix33;


//////////////////////////////////////////////////////////////////////////////
/// \struct  Quaternion
/// \brief   Quaternion
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
struct Quaternion
{
  union
  {
    TReal x, y, z, w;
    TReal e[4];
  };

  /// Ctor
  Quaternion()
	  {

  x = y = z = 0.0f;
  w = 1.0f;

}
  Quaternion(TReal _x, TReal _y, TReal _z, TReal _w)
	  {
  x = _x; y = _y; z = _z; w = _w;
}

  /// Asignacion
  void set(TReal _x, TReal _y, TReal _z, TReal _w)
	  {
  x = _x; y = _y; z = _z; w = _w;
}
  void set(const Quaternion<TReal>& q)
	  {
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}
  Quaternion<TReal>& operator = (const Quaternion<TReal>& q)
	  {
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;

  return (*this);
}

  /// Logicos
  bool operator ==(const Quaternion<TReal> &q) const
	  {
  Quaternion a = *this,
    b = q;

  a.normalize();
  b.normalize();
  b.inverse();

  a *= b;

  return a.x && a.y && a.z;
}
  bool operator !=(const Quaternion<TReal> &q) const
	  {
  return !operator==(q);
}

  /// Aritmeticos
  Quaternion<TReal> &operator ~() const                         /// Conjugado
{
  Quaternion t;

  t.x = -x;
  t.y = -y;
  t.z = -z;
  t.w = w;

  return t;
}
  Quaternion<TReal> &operator *(const Quaternion<TReal> &q) const
	  {
  Quaternion t;

  t.x = (w * q.x + x * q.w + y * q.z - z * q.y);
  t.y = (w * q.y - x * q.z + y * q.w + z * q.x);
  t.z = (w * q.z + x * q.y - y * q.x + z * q.w);
  t.w = (w * q.w - x * q.x - y * q.y - z * q.z);

  return t;
}
  Quaternion<TReal> &operator *=(const Quaternion<TReal> &q)
	  {
  Quaternion t;

  t.x = (w * q.x + x * q.w + y * q.z - z * q.y);
  t.y = (w * q.y - x * q.z + y * q.w + z * q.x);
  t.z = (w * q.z + x * q.y - y * q.x + z * q.w);
  t.w = (w * q.w - x * q.x - y * q.y - z * q.z);

  *this = t;

  return (*this);
}
  Quaternion<TReal> &operator /=(const Quaternion<TReal> &q)
	  {
  Quaternion t = q;

  return ((*this) *= t.inverse());
}
  Quaternion<TReal> &operator +=(const Quaternion<TReal> &q)
	  {
  x += q.x;   
  y += q.y;   
  z += q.z;   
  w += q.w;   

  return (*this);
}
  Quaternion<TReal> &operator -=(const Quaternion<TReal> &q)
	  {
  x -= q.x;   
  y -= q.y;   
  z -= q.z;   
  w -= q.w;   

  return (*this);
}
  Quaternion<TReal> &operator *=(TReal a)
	  {
  x *= a;   
  y *= a;   
  z *= a;   
  w *= a;   
  
  return (*this);
}
  Quaternion<TReal> &operator /=(TReal a)
	  {
  x /= a;   
  y /= a;   
  z /= a;   
  w /= a;   

  return (*this);
}

  /// Operaciones
  Quaternion<TReal> &identity()
	  {
  x = y = z = 0.0f;
  w = 1.0f;

  return (*this);
}
  Quaternion<TReal> &normalize()
	  {
  TReal len2 = x*x + y*y + z*z + w*w;
  
  if (len2 < IEMath<TReal>::EPSILON)
    identity();
  else
  {
    TReal inv = 1.0f / IEMath<TReal>::Sqrt(len2);

    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
  }

  return (*this);
}
  Quaternion<TReal> &inverse()
	  {
  TReal mag = w*w + x*x + y*y + z*z;
  TReal invMag;

  if (mag == 1.0f)    // caso especial
  {
    x = -x;
    y = -y;
    z = -z;
  }
  else
  {
    if (mag == 0.0f)
      invMag = 1.0f;
    else
      invMag = 1.0f / mag;
    
    x *= -invMag;
    y *= -invMag;
    z *= -invMag;
    w *= invMag;
  }                        

  return (*this);
}

  TReal getAngle() const
	  {
  return (TReal)(2.0f * IEMath<TReal>::ACos(w));
}
  Vector3D<TReal> &getAxis() const
	  {
  Vector3D v(x, y, z);

  if (w <= IEMath<TReal>::EPSILON)
    return v;

  return v / w;
}
  Vector3D<TReal> &rotate(const Vector3D<TReal> &v) const
	  {
  Quaternion<TReal> q;
  Vector3D<TReal> f;

  q = *this * v * (~*this);
  f.set(q.x, q.y, q.z);

  return f;
}

  Quaternion<TReal>& slerp(const Quaternion<TReal> &q, TReal a)
	  {
  TReal sign2;
  double cosOmega = x * q.x + y * q.y + z * q.z + w * q.w;

  if (cosOmega < 0.0f)
  {
    cosOmega = -cosOmega;
    sign2 = -1.0f;
  } 
  else  
    sign2 = 1.0f;

  double scale1, scale2;

  if ((1.0f - cosOmega) > IEMath<TReal>::EPSILON)
  { 
    double omega = IEMath<TReal>::ACos((TReal)cosOmega);
    double sinOmega = IEMath<TReal>::Sin((TReal)omega);
    scale1 = IEMath<TReal>::Sin((1.0 - a) * omega) / sinOmega;
    scale2 = sign2 * sin(a * omega) / sinOmega;
  } 
  else        // Estan muy cerca, pasamos a interpolacion lineal
  {
    scale1 = 1.0 - a;
    scale2 = sign2 * a;
  }

  x = TReal(scale1 * x + scale2 * q.x);
  y = TReal(scale1 * y + scale2 * q.y);
  z = TReal(scale1 * z + scale2 * q.z);
  w = TReal(scale1 * w + scale2 * q.w);

  return (*this);
}

  void fromAngles(const Vector3D<TReal> &axis, TReal angle)
	  {
  Vector3D v;
  TReal s;

  v = Vector3D::normalize(axis);

  angle /= 2.0f;

  s = IEMath<TReal>::Sin(angle);

  x = v.x * s;
  y = v.y * s;
  z = v.z * s;
  w = IEMath<TReal>::Cos(angle);
}
  void fromMatrix(const Matrix33<TReal> &m)
	  {
  // Quaternion components squared
  TReal qw2 = 0.25*(m.e[0]+m.e[4]+m.e[8]+1.0);
  TReal qx2 = qw2-0.5*(m.e[4]+m.e[8]);
  TReal qy2 = qw2-0.5*(m.e[8]+m.e[0]);
  TReal qz2 = qw2-0.5*(m.e[0]+m.e[4]);
  // Decide maximum magnitude component
  int i=(qw2>qx2)?
    ((qw2>qy2)?((qw2>qz2)?0:3) : ((qy2>qz2)?2:3)) :
  ((qx2>qy2)?((qx2>qz2)?1:3) : ((qy2>qz2)?2:3));

  TReal tmp;

  // Compute signed Quaternion components using numerically stable method
  switch (i)
    {
    case 0:
      w=IEMath<TReal>::Sqrt(qw2); tmp=0.25f/w;
      x=(m.e[7]-m.e[5])*tmp;
      y=(m.e[2]-m.e[6])*tmp;
      z=(m.e[3]-m.e[1])*tmp;
      break;
    case 1:
      x=IEMath<TReal>::Sqrt(qx2); tmp=0.25f/x;
      w=(m.e[7]-m.e[5])*tmp;
      y=(m.e[1]+m.e[3])*tmp;
      z=(m.e[6]+m.e[2])*tmp;
      break;
    case 2:
      y=IEMath<TReal>::Sqrt(qy2); tmp=0.25f/y;
      w=(m.e[2]-m.e[6])*tmp;
      x=(m.e[1]+m.e[3])*tmp;
      z=(m.e[5]+m.e[7])*tmp;
      break;
    case 3:
      z=IEMath<TReal>::Sqrt(qz2); tmp=0.25f/z;
      w=(m.e[3]-m.e[1])*tmp;
      x=(m.e[2]+m.e[6])*tmp;
      y=(m.e[5]+m.e[7])*tmp;
      break;
    }

  // Always keep all components positive
  // (note that scalar*Quaternion is equivalent to Quaternion, so q==-q)
  if (i&&w<0.0) { w=-w; x=-x; y=-y; z=-z; }

  // Normalize it to be safe
  tmp = 1.0f / IEMath<TReal>::Sqrt(w*w+x*x+y*y+z*z);
  w *= tmp;
  x *= tmp;
  y *= tmp;
  z *= tmp;
}
  void fromEuler(TReal _x, TReal _y, TReal _z)      /// Cegecimales
	  {
  TReal rx, ry, rz, ti, tj, tk;
  Quaternion qx, qy, qz;

  // Convert angles to radians
  rx = _x * IEMath<TReal>::DEG_TO_RAD;
  ry = _y * IEMath<TReal>::DEG_TO_RAD;
  rz = _z * IEMath<TReal>::DEG_TO_RAD;

  // Get half angles
  ti = rx * 0.5;
  tj = ry * 0.5;
  tk = rz * 0.5;

  // Quaternion
  qx.x = sin(ti); qx.y = 0; qx.z = 0; qx.w = cos(ti);
  qy.x = 0; qy.y = sin(tj); qy.z = 0; qy.w = cos(tj);
  qz.x = 0; qz.y = 0; qz.z = sin(tk); qz.w = cos(tk);

  // qx, qy
  w = qx.w * qy.w - qx.x * qy.x - qx.y * qy.y - qx.z * qy.z;
  x = qx.w * qy.x + qx.x * qy.w + qx.y * qy.z - qx.z * qy.y;
  y = qx.w * qy.y - qx.x * qy.z + qx.y * qy.w + qx.z * qy.x;
  z = qx.w * qy.z + qx.x * qy.y - qx.y * qy.x + qx.z * qy.w;

  // qz
  w = w * qz.w - x * qz.x - y * qz.y - z * qz.z;
  x = w * qz.x + x * qz.w + y * qz.z - z * qz.y;
  y = w * qz.y - x * qz.z + y * qz.w + z * qz.x;
  z = w * qz.z + x * qz.y - y * qz.x + z * qz.w;
}

  operator Matrix33<TReal>() const
	  {
  Matrix33 m;

  m.m00 = (TReal)2.0f * ((x * x  - (TReal) 0.5f) + (y * y));
  m.m01 = (TReal)2.0f * ((y * z) + (x * w));
  m.m02 = (TReal)2.0f * ((y * w) - (x * z));

  m.m10 = (TReal)2.0f * ((y * z) - (x * w));
  m.m11 = (TReal)2.0f * ((x * x  - (TReal)0.5f) + (z * z));
  m.m12 = (TReal)2.0f * ((z * w) + (x * y));

  m.m20 = (TReal)2.0f * ((y * w) + (x * z));
  m.m21 = (TReal)2.0f * ((z * w) - (x * y));
  m.m22 = (TReal)2.0f * ((x * x  - (TReal)0.5f) + (w * w));

  return m;
}


  /// Logs
  friend __declspec(dllimport) std::ostream &operator<< (std::ostream &o, const Quaternion<TReal> &q)
{
  o << "Quaternion(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";

  return o;
}
  /// Quaternion especial
  static const Quaternion IDENTITY;
};


inline Quaternion<F32> &operator *(const Quaternion<F32> q, const Vector3D<F32> v)
{
  return Quaternion<F32>(-(q.x*v.x + q.y*v.y + q.z*v.z),q.w*v.x + q.y*v.z - q.z*v.y,q.w*v.y + q.z*v.x - q.x*v.z,  q.w*v.z + q.x*v.y - q.y*v.x);
}
inline Quaternion<F64> &operator *(const Quaternion<F64> q, const Vector3D<F64> v)
{
  return Quaternion<F64>(-(q.x*v.x + q.y*v.y + q.z*v.z),q.w*v.x + q.y*v.z - q.z*v.y,
    q.w*v.y + q.z*v.x - q.x*v.z,
    q.w*v.z + q.x*v.y - q.y*v.x);
}
inline Quaternion<F80> &operator *(const Quaternion<F80> q, const Vector3D<F80> v)
{
  return Quaternion<F80>(-(q.x*v.x + q.y*v.y + q.z*v.z),
    q.w*v.x + q.y*v.z - q.z*v.y,
    q.w*v.y + q.z*v.x - q.x*v.z,
    q.w*v.z + q.x*v.y - q.y*v.x);
}

inline Quaternion<F32> &operator *(const Vector3D<F32> v, const Quaternion<F32> q)
{
  return Quaternion<F32>(-(q.x*v.x + q.y*v.y + q.z*v.z),
    q.w*v.x + q.z*v.y - q.y*v.z,
    q.w*v.y + q.x*v.z - q.z*v.x,
    q.w*v.z + q.y*v.x - q.x*v.y);
}
inline Quaternion<F64> &operator *(const Vector3D<F64> v, const Quaternion<F64> q)
{
  return Quaternion<F64>(-(q.x*v.x + q.y*v.y + q.z*v.z),
    q.w*v.x + q.z*v.y - q.y*v.z,
    q.w*v.y + q.x*v.z - q.z*v.x,
    q.w*v.z + q.y*v.x - q.x*v.y);
}
inline Quaternion<F80> &operator *(const Vector3D<F80> v, const Quaternion<F80> q)
{
  return Quaternion<F80>(-(q.x*v.x + q.y*v.y + q.z*v.z),
    q.w*v.x + q.z*v.y - q.y*v.z,
    q.w*v.y + q.x*v.z - q.z*v.x,
    q.w*v.z + q.y*v.x - q.x*v.y);
}


#endif // _QUAT_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End Of File
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
