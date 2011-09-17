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
#ifndef __I386_H__
#define __I386_H__
#include <xmmintrin.h>


#define  SHUFFLE_PARAM(x,y,z,w) ((x) | ((y << 2) | ((z) << 4) | ((w) << 6)))

#define _mm_replicate_x_ps(v) _mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))

#define _mm_replicate_y_ps(v)	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))

#define _mm_replicate_z_ps(v)	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))

#define _mm_replicate_w_ps(v)	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(3, 3, 3, 3))

#define _mm_madd_ps(a,b,c)	_mm_add_ps(_mm_mul_ps((a), (b)), (c))


__m128 operator+(__m128 a,__m128 b)
{
	__m128 r;

	_asm
	{
		movaps xmm0, xmmword ptr[a]
		movaps xmm1, xmmword ptr[b]
		addps xmm0, xmm1
		movaps xmmword ptr[r], xmm0
	}

	return r;
}


__m128 operator-(__m128 a,__m128 b)
{
	__m128 r;
	_asm
	{
		movaps xmm0, xmmword ptr[a]
		movaps xmm1, xmmword ptr[b]
		subps xmm0, xmm1
		movaps xmmword ptr[r], xmm0
	}

	return r;
}

__m128 operator*(__m128 a,__m128 b)
{
	__m128 r;
	_asm
	{
		movaps xmm0, xmmword ptr[a]
		movaps xmm1, xmmword ptr[b]
		mulps xmm0, xmm1
		movaps xmmword ptr[r], xmm0
	}

	return r;
}

__m128 operator/(__m128 a,__m128 b)
{
	__m128 r;
	_asm
	{
		movaps xmm0, xmmword ptr[a]
		movaps xmm1, xmmword ptr[b]
		divps xmm0, xmm1
		movaps xmmword ptr[r], xmm0
	}

	return r;
}








#endif