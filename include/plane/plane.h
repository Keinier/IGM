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
#ifndef __PLANE_H__
#define __PLANE_H__

#include <IEMath\vector\vector.h>

template<typename TReal> 
class Plane
{
	typedef Vector3D<TReal> Point,Vector;
	typedef Vector4D<TReal> dPlane;


	Plane(TReal d,Vector v)
	{		
		_v.x=v.x;
		_v.y=v.y;
		_v.z=v.z;
		_v.v=d;
	}
	Plane(dPlane v)
	{		
		_v.x=v.x;
		_v.y=v.y;
		_v.z=v.z;
		_v.v=v.v;
	}

	Plane(){}

	Vector& GetNormal(VOID)
	{
		Vector tmp;
		tmp.x=_v.x;
		tmp.y=_v.y;
		tmp.z=_v.z;

		return tmp.normalize();
	}
	VOID SetNormal(Vector& normal)
	{
		Vector tmp = normal.normalize();
		_v.x = tmp.x;
		_v.y=tmp.y;
		_v.z=tmp.z;

	}
	
	Point GetPoint(VOID)
	{
		return P0;
	}
	VOID SetPoint(Point &p)
	{
		P0 = p;
	}

	TReal Distance(VOID)
	{
	}

	dPlane _v;
	
};


#endif