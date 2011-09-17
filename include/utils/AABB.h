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
#ifndef __AABB_H__
#define __AABB_H__

#include <IEMath\vector\vector.h>

template<typename TReal>
class AABB
{
public:
	typedef Vector3D<TReal> Point;

	AABB()
	{}

	AABB(Point pmin,Point pmax)
	{
		m_Pmax = pmax;
		m_Pmin = pmin;
	}

	//sets

	VOID SetPmin(Point p)
	{
		m_Pmin = p;
	}
	VOID SetPmax(Point p)
	{
		m_Pmax = p;
	}

	BOOL IsInSide(Point &p)
	{
		return ((p.x >= m_Pmin.x) && (p.x <= m_Pmax.x) &&
				(p.y >= m_Pmin.y) && (p.y <= m_Pmax.y) &&
				(p.z >= m_Pmin.z) && (p.z >= m_Pmax.z));

	}

protected:
	Point m_Pmax;
	Point m_Pmin;

};
#endif 