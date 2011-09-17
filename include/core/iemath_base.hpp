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
#ifndef __IEMATH_BASE_HPP__
#define __IEMATH_BASE_HPP__

#include <IEMath\core\iemath_core.hpp>


template<class TReal,U8 Rows,U8 Cols>class Base
{
public:
	enum {NumRows = Rows,NumCols = Cols};

	Base(){
		SetNull();
	}
	VOID SetNull(VOID)
	{
		for(U8 i=0;i<Rows;i++)
		{
			for(U8 j=0;j<Cols;j++)
			{
				m_data[i][j] = 0;
			}
		}
	}
	Base(TReal values[Rows][Cols])
{
		for(U8 i=0;i<Rows;i++)
		{
			for(U8 j=0;j<Cols;j++)
			{
				m_data[i][j] =values[i][j];
			}
		}
}
	VOID SetData(TReal dat,U8 i,U8 j){m_data[i][j]=dat;}
	TReal GetData(U8 i,U8 j){ return m_data[i][j]; }
	TReal* Data(){ return &m_data[0][0];};
	
	// operadores unarios
	Base operator-(VOID)
	{
		Base tmp;
		for(U8 i=0;i<Rows;i++)
		{
			for(U8 j=0;j<Colss;j++)
			{
				tmp.SetData(-(m_data[i][j]),i,j);
			}
		}
		return tmp;
	}

	BOOL IsNull(VOID)
	{
		
		for(U8 i=0;i<Rows;i++)
		{
			for(U8 j=0;j<Cols;j++)
			{
				if(m_data[i][j] == 0){
					return true;
				}				
					
			}
		}
		return false;

	}
	TReal m_data[Rows][Cols];
};


#endif // __IEMATH_BASE_HPP__