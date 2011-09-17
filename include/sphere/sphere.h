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
#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <IEMath\vector\vector.h>

template<typename TReal> class Sphere
{
public:
	Sphere(Vector3D<TReal> pos,TReal radi)
	{
		comp.set(pos.x,pos.y,pos.z,radi);
		r=radi
	}
	Sphere(Vector4D<TReal> q)
	{
		comp = q;
	}


	VOID SetR(TReal r)
	{
		comp.v = r;
	}
	TReal GetR(VOID)
	{
		return comp.v;
	}

	VOID SetPos(Vector3D<TReal> pos)
	{
		comp.x = pos.x;
		comp.y = pos.y;
		comp.z = pos.z;
	}
	Vector3D<TReal> GetPos(VOID)
	{
		return Vector3D(comp.x,comp.y,comp.z);
	}


	Vector4D<TReal> comp;
};
#endif