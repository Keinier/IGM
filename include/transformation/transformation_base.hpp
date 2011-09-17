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
#ifndef __TRANSFORMATION_BASE_HPP__
#define __TRANSFORMATION_BASE_HPP__

#include <IEMath\matrix\matrix_type.hpp>
#include <IEMath\vector\vector_type.hpp>
#include <IEMath\vector\vector_operations.hpp>
#include <IEMath\quaternio\quaternio.hpp>


template<typename TReal>
class Transformation:public CMatrix44<TReal>
{
public:
	Transformation():CMatrix44(){}
	virtual CVector3D<TReal> Apply(CVector3D<TReal> vp)=0;
	virtual CMatrix44<TReal> asMatrix(VOID) = 0;

};


template<typename TReal>
class TRotationQ:public CQuaternion<TReal>
{
public:
	TRotationQ():CQuaternion(){}
	TRotationQ(CQuaternion<TReal> qr):CQuaternion(qr){}

	virtual CVector3D<TReal> Apply(CVector3D<TReal> vp)
	{
		CVector3D<TReal> tmp;
		
		tmp = (this * tmp) * Inverse();
	return tmp;
	};
	virtual CMatrix44<TReal> asMatrix(VOID)
	{
		CMatrix44<TReal> tmp;
		for(U8 i=0;i<NumRows;i++)
		{
			for(U8 j=0;j<NumCols;j++)
			{
				tmp.SetData(m_data[i][j],i,j);
			}
		}
		return tmp;
	}
};
template<typename TReal>
class TRotationX:public Transformation<TReal>
{
public:
	TRotationX():Transformation(){}
	TRotationX(TReal angle)
	{
		SetIdent();

		m_data[1][1] = IEMath<TReal>::Cos(angle);
		m_data[1][2] = IEMath<TReal>::Sin(angle);
		m_data[2][1] = -(IEMath<TReal>::Sin(angle));
		m_data[2][2] = IEMath<TReal>::Cos(angle);
	}

	virtual CVector3D<TReal> Apply(CVector3D<TReal> vp)
	{
		CVector3D<TReal> tmp;
		tmp = (vp * asMatrix());
	return tmp;
	};
	virtual CMatrix44<TReal> asMatrix(VOID)
	{
		CMatrix44<TReal> tmp;
		for(U8 i=0;i<NumRows;i++)
		{
			for(U8 j=0;j<NumCols;j++)
			{
				tmp.SetData(m_data[i][j],i,j);
			}
		}
		return tmp;
	}
};
template<typename TReal>
class TRotationY:public Transformation<TReal>
{
public:
	TRotationY():Transformation(){}
	TRotationY(TReal angle)
	{
		SetIdent();

		m_data[0][0] = IEMath<TReal>::Cos(angle);
		m_data[0][2] = -(IEMath<TReal>::Sin(angle));
		m_data[2][0] = IEMath<TReal>::Sin(angle);
		m_data[2][2] = IEMath<TReal>::Cos(angle);
	}

	virtual CVector3D<TReal> Apply(CVector3D<TReal> vp)
	{
		CVector3D<TReal> tmp;
		tmp = (vp * asMatrix());
	return tmp;
	};
	virtual CMatrix44<TReal> asMatrix(VOID)
	{
		CMatrix44<TReal> tmp;
		for(U8 i=0;i<NumRows;i++)
		{
			for(U8 j=0;j<NumCols;j++)
			{
				tmp.SetData(m_data[i][j],i,j);
			}
		}
		return tmp;
	}
};


template<typename TReal>
class TRotationZ:public Transformation<TReal>
{
public:
	TRotationZ():Transformation(){}
	TRotationZ(TReal angle)
	{
		SetIdent();

		m_data[0][0] = IEMath<TReal>::Cos(angle);
		m_data[0][1] = IEMath<TReal>::Sin(angle);
		m_data[1][0] = -(IEMath<TReal>::Sin(angle));
		m_data[1][2] = IEMath<TReal>::Cos(angle);
	}

	virtual CVector3D<TReal> Apply(CVector3D<TReal> vp)
	{
		CVector3D<TReal> tmp;
		tmp = (vp * asMatrix());
	return tmp;
	};
	virtual CMatrix44<TReal> asMatrix(VOID)
	{
		CMatrix44<TReal> tmp;
		for(U8 i=0;i<NumRows;i++)
		{
			for(U8 j=0;j<NumCols;j++)
			{
				tmp.SetData(m_data[i][j],i,j);
			}
		}
		return tmp;
	}
};

template<typename TReal>
class TTranslation:public Transformation<TReal>
{
public:
	TTranslation():Transformation(){}
	TTranslation(CVector3D<TReal> vt)
	{
		SetIdent();

		m_data[3][0] = vt.m_data[0][0];
		m_data[3][1] = vt.m_data[0][1];
		m_data[3][2] = vt.m_data[0][2];
	}
	TTranslation(TReal tx,TReal ty,TReal tz)
	{
		SetIdent();

		m_data[3][0] = tx;
		m_data[3][1] = ty;
		m_data[3][2] = tz;
	}
	virtual CVector3D<TReal> Apply(CVector3D<TReal> vp)
	{
		CVector3D<TReal> tmp;
		tmp = (vp * asMatrix());
	return tmp;
	};
	virtual CMatrix44<TReal> asMatrix(VOID)
	{
		CMatrix44<TReal> tmp;
		for(U8 i=0;i<NumRows;i++)
		{
			for(U8 j=0;j<NumCols;j++)
			{
				tmp.SetData(m_data[i][j],i,j);
			}
		}
		return tmp;
	}
};

template<typename TReal>
class TScale:public Transformation<TReal>
{
public:
	TScale():Transformation(){}
	TScale(CVector3D<TReal> vs)
	{
		SetIdent();

		m_data[0][0] = vs.m_data[0][0];
		m_data[1][1] = vs.m_data[0][1];
		m_data[2][2] = vs.m_data[0][2];
	}
	TScale(TReal sx,TReal sy,TReal sz)
	{
		SetIdent();

		m_data[0][0] = sx;
		m_data[1][1] = sy;
		m_data[2][2] = sz;
	}
	virtual CVector3D<TReal> Apply(CVector3D<TReal> vp)
	{
		CVector3D<TReal> tmp;
		tmp = (vp * asMatrix());
	return tmp;
	};
	virtual CMatrix44<TReal> asMatrix(VOID)
	{
		CMatrix44<TReal> tmp;
		for(U8 i=0;i<NumRows;i++)
		{
			for(U8 j=0;j<NumCols;j++)
			{
				tmp.SetData(m_data[i][j],i,j);
			}
		}
		return tmp;
	}
};

#endif // __TRANSIFRMATION_HPP__