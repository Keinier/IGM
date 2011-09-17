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
#ifndef __SIMD_SSE_H__
#define __SIMD_SSE_H__
#define _ASSEMBLY_

#ifdef _ASSEMBLY_
#include <IEMath\SSE\i386\i386.h>
#else
#include <IEMath\SSE\generic\generic.h>
#endif

__m128 load(float *v)
{
	return _mm_load_ps(v);
}

void restore(float* f,__m128 v)
{
	_mm_store_ps(f,v);
}

typedef	__m128 F128;
__m128 mulVecMatrix(__m128 &v,__m128 &r0,__m128 &r1,__m128 &r2,__m128 &r3)
{

	F128 result;
	
	result = (_mm_replicate_x_ps(v) * r0);
	result = ((_mm_replicate_x_ps(v) * r1) + result);
	result = ((_mm_replicate_x_ps(v) * r2) + result);
	result = ((_mm_replicate_x_ps(v) * r3) + result);
	return result;
}
#endif