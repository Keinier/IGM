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
#ifndef _VECTOR_H
#define _VECTOR_H

#include <istream>
#include <IEMath\core\iemath_core.hpp>


//////////////////////////////////////////////////////////////////////////////
/// \struct  Vector2D
/// \brief   Vector 2D
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
struct Vector2D
{
  union
  {
    struct { TReal x, y; };
    struct { TReal width, height; };
    TReal v[2];
  };

  /// Ctor
	Vector2D()
	{
		 x = y = 0.0;
	}

	Vector2D(const Vector2D<TReal>& v)
	{
		x = v.x;
		y = v.y;
	}

	Vector2D(TReal _x, TReal _y)
	{
		x = _x;
		y = _y;
	}

	Vector2D(TReal comp[])
	{
		x = comp[0];
		y = comp[1];
	}

  /// Asignacion
  const Vector2D<TReal>& set(TReal _x, TReal _y)
  {
	x = _x;
	y = _y;
	return (*this);
  }	

  const Vector2D<TReal>& set(TReal comp[])
{
  x = comp[0];
  y = comp[1];

  return (*this);
}
  Vector2D<TReal>& operator = (const Vector2D<TReal>& v)
{
  x = v.x;
  y = v.y;

  return (*this);
}

  /// Vector nulo
  const Vector2D<TReal>& clear()
{
  x = y = 0.0;
  return (*this);
}

  /// Logicos
  bool operator == (const Vector2D<TReal>& v) const     /// Igualdad
{
  return (x == v.x) && (y == v.y);
}
  bool operator != (const Vector2D<TReal>& v) const     /// Desigualdad
  {
  return (x != v.x) || (y != v.y);
}

  bool operator <= (const Vector2D<TReal>& v) const     /// Menor igual
{
  return len2() <= v.len2();
}

  bool operator >= (const Vector2D<TReal>& v) const     /// Mayor igual
{
  return len2() >= v.len2();
}
  bool operator <  (const Vector2D<TReal>& v) const     /// Menor
{
  return len2() < v.len2();
}
 bool operator >  (const Vector2D<TReal>& v) const     /// Mayor
{
  return len2() > v.len2();
}

  /// Aritmeticos
  Vector2D<TReal> operator - () const                   /// Negativo
{
  return Vector2D<TReal>(-x, -y);
}
  Vector2D<TReal> operator + (const Vector2D<TReal>& v) const      /// Suma
{
  return Vector2D<TReal>(x + v.x, y + v.y);
}
  Vector2D<TReal> operator - (const Vector2D<TReal>& v) const      /// Resta
{
  return Vector2D(x - v.x, y - v.y);
}
  
  Vector2D<TReal> operator * (TReal scalar) const        /// Multiplicacion por escalar
{
  return Vector2D<TReal>(x * scalar, y * scalar);
}
  
  Vector2D<TReal> operator * (Vector2D<TReal> &v) const            /// Multiplicacion por vector
{
  return Vector2D<TReal>(x * v.x, y * v.y);
}
  
  Vector2D<TReal> operator / (TReal scalar) const        /// Division por escalar
  {
  TReal inv = 1.0f / scalar;
  return Vector2D<TReal>(x * inv, y * inv);
}

  Vector2D<TReal> operator / (Vector2D<TReal> &v) const            /// Division por vector
  {
  return Vector2D<TReal>(x / v.x, y / v.y);
	}

  Vector2D<TReal>& operator += (const Vector2D<TReal>& v)          /// Suma aditiva
  {
  x += v.x;
  y += v.y;
  
  return (*this);
}

  Vector2D<TReal>& operator -= (const Vector2D<TReal>& v)          /// Resta aditiva
  {
  x -= v.x;
  y -= v.y;
  
  return (*this);
}

  Vector2D<TReal>& operator *= (TReal scale)             /// Multiplicacion por escalar aditiva
  {
  x *= scale;
  y *= scale;
  
  return (*this);
}
 
  Vector2D<TReal>& operator *= (Vector2D<TReal> &v)                /// Multiplicacion por vector aditiva
  {
  x *= v.x;
  y *= v.y;

  return (*this);
}

  Vector2D<TReal>& operator /= (TReal scale)             /// Division por escalar aditiva
  {
  x /= scale;
  y /= scale;
  
  return (*this);
 }


 Vector2D<TReal>& operator /= (Vector2D<TReal> &v)                /// Division por vector aditiva
 {
  x /= v.x;
  y /= v.y;

  return (*this);
 }

  /// Misc
  TReal dot(const Vector2D<TReal>& v) const              /// Producto escalar
 {
  return (x * v.x) + (y * v.y);
 }
  
  const Vector2D<TReal>& projectOnto(const Vector2D<TReal> &v)     /// Proyeccion en vector
  {
  return v * (dot(v) / v.dot(v));
  }
 
  TReal angle(const Vector2D<TReal> &v)                  /// Angulo con otro vector
  {
  TReal mag = len() * v.len();

  if (mag == 0.0)
    return 0;

  return (TReal)IEMath<TReal>::ACos(dot(v) / mag);
}
	  
  
  TReal len() const                           /// Longitud
  {
  return IEMath<TReal>::Sqrt(x*x + y*y);
  }
	
  TReal len2() const                          /// Longitud cuadrada
{
  return (TReal)(x*x + y*y);   /// lo mismo que this->dot(this)
}
  
  
  const Vector2D<TReal>& normalize()                    /// Normalizar
  {
  TReal a = len();
  TReal b = 1.0f / a;

  x *= b;
  y *= b;

  return (*this);
}
	  
  const Vector2D<TReal>& invert()                       /// Invierte
	  {
  x = -x;
  y = -y;

  return (*this);
}
  
  TReal distance(const Vector2D<TReal>& v) const         /// Distancia a vector
  {
  return (v - *this).len();
  }
  /// Logs
  friend __declspec(dllimport) std::ostream& operator<< (std::ostream& o, const Vector2D<TReal>& v)
{
  o << "Vector2D(" << v.x << ", " << v.y << ")";

  return o;
}

} ;




//////////////////////////////////////////////////////////////////////////////
/// \struct  Vector3D
/// \brief   Vector 3D
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
struct Vector3D
{
  union
  {
    struct { TReal x, y, z; };
    TReal v[3];
  };

  /// Ctor
  Vector3D()
{

  x = y = z = 0.0;

}

  Vector3D(const Vector3D<TReal>& v)
{
  x = v.x;
  y = v.y;
  z = v.z;
}

  Vector3D(TReal _x, TReal _y, TReal _z)
	  {
  x = _x;
  y = _y;
  z = _z;
}
  Vector3D(TReal comp[])
{
  x = comp[0];
  y = comp[1];
  z = comp[2];
}

  Vector3D(const Vector2D<TReal>& v)
{
  x = v.x;
  y = v.y;
  z = 0.0;
}


  /// Asignacion
  const Vector3D<TReal>& set(TReal _x, TReal _y, TReal _z)
	  {
  x = _x;
  y = _y;
  z = _z;

  return (*this);
}

  const Vector3D<TReal>& set(TReal comp[])
	{
  x = comp[0];
  y = comp[1];
  z = comp[2];

  return (*this);
}

  Vector3D<TReal>& operator = (const Vector3D<TReal>& v)
	  {
  x = v.x;
  y = v.y;
  z = v.z;

  return (*this);
}

  /// Vector nulo
  const Vector3D<TReal>& clear()
  {
  x = y = z = 0.0;

  return (*this);
}
  /// Logicos
  bool operator == (const Vector3D<TReal>& v) const           /// Igualdad
	  {
  return (x == v.x) && (y == v.y) && (z == v.z);
}

  bool operator != (const Vector3D<TReal>& v) const           /// Desigualdad
	  {
  return (x != v.x) || (y != v.y) || (z != v.z);
}
  bool operator <= (const Vector3D<TReal>& v) const           /// Menor igual
	  {
  return len2() <= v.len2();
}
  bool operator >= (const Vector3D<TReal>& v) const           /// Mayor igual
	  {
  return len2() >= v.len2();
}
  bool operator <  (const Vector3D<TReal>& v) const           /// Menor
	  {
  return len2() < v.len2();
}
  bool operator >  (const Vector3D<TReal>& v) const           /// Mayor
	  {
  return len2() > v.len2();
}

  /// Aritmeticos
  Vector3D<TReal> operator - () const                         /// Negativo
	  {
  return Vector3D<TReal>(-x, -y, -z);
}
  Vector3D<TReal> operator + (const Vector3D<TReal>& v) const            /// Suma
	  {
  return Vector3D<TReal>(x + v.x, y + v.y, z + v.z);
}
  Vector3D<TReal> operator - (const Vector3D<TReal>& v) const            /// Resta
	  {
  return Vector3D<TReal>(x - v.x, y - v.y, z - v.z);
}
  Vector3D<TReal> operator * (TReal scalar) const              /// Multiplicar por escalar
 {
  return Vector3D<TReal>(x * scalar, y * scalar, z * scalar);
}
  
  Vector3D<TReal> operator / (TReal scalar) const              /// Dividir por escalar
{
  TReal inv = 1.0f / scalar;

  return Vector3D<TReal>(x * inv, y * inv, z * inv);
}
  Vector3D<TReal>& operator += (const Vector3D<TReal>& v)           /// Suma aditiva
	  {
  x += v.x;
  y += v.y;
  z += v.z;

  return (*this);
}
  Vector3D<TReal>& operator -= (const Vector3D<TReal>& v)                /// Resta aditiva
 {
  x -= v.x;
  y -= v.y;
  z -= v.z;

  return (*this);
}
  Vector3D<TReal>& operator *= (TReal scalar)                  /// Multiplicacion aditiva
 {
  x *= scalar;
  y *= scalar;
  z *= scalar;

  return (*this);
 }
Vector3D<TReal>& operator /= (TReal scalar)                  /// Division aditiva
{
  TReal inv = 1.0f / scalar;

  x *= inv;
  y *= inv;
  z *= inv;

  return (*this);
}
  /// Misc

  const Vector3D<TReal>& projectOnto(const Vector3D<TReal> &v)           /// Proyeccion en vector
  {
  return (dot(v) / v.dot(v)) * v;
}
  
  TReal angle(const Vector3D<TReal> &v)                        /// Angulo con otro vector
  {
  TReal mod = len() * v.len();

  if (mod == 0.0)
    return 0;

  return (TReal)IEMath<TReal>::ACos(dot(v) / mod);
}
	  
  TReal len() const                                 /// Longitud
  {
  return IEMath<TReal>::Sqrt(x*x + y*y + z*z);
}
  
  TReal len2() const                                /// Longitud cuadrada
  {
  return (TReal)(x*x + y*y + z*z);
}
  
  TReal dot(const Vector3D<TReal>& v) const                    /// Producto escalar (Dot)
  {
  return (x*v.x + y*v.y + z*v.z);
}

  TReal operator * (const Vector3D<TReal>& v) const            /// Producto escalar (Dot)
  {
  return (x*v.x + y*v.y + z*v.z);
}
  
  Vector3D<TReal> cross(const Vector3D<TReal>& v) const                  /// Producto vectorial (Cross product)
  {
  return Vector3D<TReal>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
  
  Vector3D<TReal> operator % (const Vector3D<TReal>& v) const            /// Producto vectorial (Cross product)
  {
  return Vector3D<TReal>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
  
  Vector3D<TReal>& normalize() /// Normalizar
  {
  TReal inv = 1.0f / len();

  x *= inv;
  y *= inv;
  z *= inv;

  return (*this);
}
  static Vector3D<TReal> normalize(const Vector3D<TReal>& v)             /// Normalizar un vector
  {
  Vector3D<TReal> vTmp(v);
  TReal inv = 1.0f / vTmp.len();

  vTmp.x *= inv;
  vTmp.y *= inv;
  vTmp.z *= inv;

  return vTmp;
}
  const Vector3D<TReal>& invert()                             /// Invierte
  {
  x = -x;
  y = -y;
  z = -z;

  return (*this);
}
  
  TReal distance(const Vector3D<TReal>& v) const               /// Distancia a un vector
{
  return (v - *this).len();
}
  /// Logs
  friend __declspec(dllimport) std::ostream& operator<< (std::ostream& o, const Vector3D<TReal>& v)
	  { 
  o << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ")";

  return o;
}


};


//////////////////////////////////////////////////////////////////////////////
/// \struct  Vector4D
/// \brief   Vector 4D
/// \author  Martin B.R. \version 1.0 \date 15/03/2003 01:07:37
//////////////////////////////////////////////////////////////////////////////
template<typename TReal>
struct Vector4D
{
  union
  {
    struct { TReal x, y, z, rhw; };
    TReal v[4];



  };

  /// Ctor
  Vector4D()
	  {
  x = y = z = 0.0;
  rhw = 1.0;
}

  Vector4D(const Vector4D<TReal>& v)
	  {
  x = v.x;
  y = v.y;
  z = v.z;
  rhw = v.rhw;
}	
  Vector4D(TReal _x, TReal _y, TReal _z, TReal _rhw = 1.0)
	  {
  x = _x;
  y = _y;
  z = _z;
  rhw = rhw;
}
  Vector4D(TReal comp[])
	  {
  x = comp[0];
  y = comp[1];
  z = comp[2];
  rhw = comp[3];
}
  Vector4D(const Vector3D<TReal>& v)
	  {
  x = v.x;
  y = v.y;
  z = v.z;
}

  /// Asignacion
  const Vector4D<TReal>& set(TReal _x, TReal _y, TReal _z, TReal _rhw = 1.0)
	  {
  x = _x;
  y = _y;
  z = _z;
  rhw = _rhw;

  return (*this);
}
  const Vector4D<TReal>& set(TReal comp[])
	  {
  x = comp[0];
  y = comp[1];
  z = comp[2];
  rhw = comp[3];

  return (*this);
}
  Vector4D<TReal>& operator = (const Vector4D<TReal>& v)
	  {
  x = v.x;
  y = v.y;
  z = v.z;
  rhw = v.rhw;

  return (*this);
}

  /// Vector nulo
  const Vector4D<TReal>& clear()
	  {
  x = y = z = 0.0;
  rhw = 1.0;

  return (*this);
}

  /// Logicos
  bool operator == (const Vector4D<TReal>& v) const   /// Igualdad
	  {
  return (x == v.x) && (y == v.y) && (z == v.z) && (rhw == v.rhw);
}
  bool operator != (const Vector4D<TReal>& v) const   /// Desigualdad
	  {
  return (x != v.x) || (y != v.y) || (z != v.z) || (rhw != v.rhw);
}
  bool operator <= (const Vector4D<TReal>& v) const   /// Menor igual
	  {
  return len2() <= v.len2();
}
  bool operator >= (const Vector4D<TReal>& v) const   /// Mayor igual
	  {
  return len2() >= v.len2();
}
  bool operator <  (const Vector4D<TReal>& v) const   /// Menor
	  {
  return len2() < v.len2();
}
  bool operator >  (const Vector4D<TReal>& v) const   /// Mayor
	  {
  return len2() > v.len2();
}

  /// Aritmeticos
  Vector4D operator - () const                 /// Negativo
	  {
  return Vector4D(-x, -y, -z, 1.0);
}
  Vector4D operator + (const Vector4D<TReal>& v) const    /// Suma
	  {
  return Vector4D(x + v.x, y + v.y, z + v.z, 1.0);
}
  Vector4D operator - (const Vector4D<TReal>& v) const    /// Resta
	  {
  return Vector4D(x - v.x, y - v.y, z - v.z, 1.0);
}
  Vector4D operator * (TReal scalar) const      /// Multiplicar por escalar
	  {
  return Vector4D(x * scalar, y * scalar, z * scalar, 1.0);
}
  Vector4D operator / (TReal scalar) const      /// Dividir por escalar
	  {
  TReal inv = 1.0f / scalar;

  return Vector4D(x * inv, y * inv, z * inv, 1.0);
}
  Vector4D<TReal>& operator += (const Vector4D<TReal>& v)        /// Suma aditiva
	  {
  x += v.x;
  y += v.y;
  z += v.z;

  return (*this);
}
  Vector4D<TReal>& operator -= (const Vector4D<TReal>& v)        /// Resta aditiva
	  {
  x -= v.x;
  y -= v.y;
  z -= v.z;

  return (*this);
}
  Vector4D<TReal>& operator *= (TReal scalar)          /// Multiplicacion aditiva
	  {
  x *= scalar;
  y *= scalar;
  z *= scalar;

  return (*this);
}
  Vector4D<TReal>& operator /= (TReal scalar)          /// Division aditiva
	  {
  TReal inv = 1.0f / scalar;

  x *= inv;
  y *= inv;
  z *= inv;

  return (*this);
}

  /// Misc
  TReal len() const                         /// Longitud
  {
  return IEMath<TReal>::Sqrt(x*x + y*y + z*z);
}
  
  TReal len2() const                        /// Longitud cuadrada
	  {
  return (TReal)(x*x + y*y + z*z);
}
  TReal dot(const Vector4D<TReal>& v) const            /// Producto escalar (Dot)
	  {
  return (x*v.x + y*v.y + z*v.z);
}
  TReal operator * (const Vector4D<TReal>& v) const    /// Producto escalar (Dot)
	  {
  return (x*v.x + y*v.y + z*v.z);
}
  Vector4D cross(const Vector4D<TReal>& v) const          /// Producto vectorial (Cross product)
  {
  return Vector4D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x, 1.0);
}
  
  Vector4D operator % (const Vector4D<TReal>& v) const    /// Producto vectorial (Cross product)
  {
  return Vector4D(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x, 1.0);
}
  Vector4D<TReal>& normalize()                        /// Normalizar
	  {
  TReal inv = 1.0f / len();

  x *= inv;
  y *= inv;
  z *= inv;
  rhw = 1.0;

  return (*this);
}
  TReal distance(const Vector4D<TReal>& v) const       /// Distancia
  {
  return (v - *this).len();
}
  /// Logs
  friend __declspec(dllimport) std::ostream& operator<< (std::ostream& o, const Vector4D<TReal>& v)
  {
  o << "Vector4D(" << v.x << ", " << v.y << ", " << v.z << ", " << v.rhw << ")";

  return o;
}

};



#endif // _VECTOR_H
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End Of File
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
