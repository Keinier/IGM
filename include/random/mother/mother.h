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
#ifndef __RAMDOM_MOTHER_H__
#define __RAMDOM_MOTHER_H__


#include <string.h>

static short mother1[10];
static short mother2[10];
static short mStart=1;

#define m16Long 65536L				/* 2^16 */
#define m16Mask 0xFFFF          /* mask for lower 16 bits */
#define m15Mask 0x7FFF			/* mask for lower 15 bits */
#define m31Mask 0x7FFFFFFF     /* mask for 31 bits */
#define m32Double  4294967295.0  /* 2^32-1 */




double Mother(unsigned long *pSeed)
{
	unsigned long  number,
						number1,
						number2;
	short n,
			*p;
	unsigned short sNumber;

		/* Initialize motheri with 9 random values the first time */
	if (mStart) {
		sNumber= *pSeed&m16Mask;   /* The low 16 bits */
		number= *pSeed&m31Mask;   /* Only want 31 bits */

		p=mother1;
		for (n=18;n--;) {
			number=30903*sNumber+(number>>16);   /* One line 
multiply-with-cary */
			*p++=sNumber=number&m16Mask;
			if (n==9)
				p=mother2;
		}
		/* make cary 15 bits */
		mother1[0]&=m15Mask;
		mother2[0]&=m15Mask;
		mStart=0;
	}

		/* Move elements 1 to 8 to 2 to 9 */
	memmove(mother1+2,mother1+1,8*sizeof(short));
	memmove(mother2+2,mother2+1,8*sizeof(short));

		/* Put the carry values in numberi */
	number1=mother1[0];
	number2=mother2[0];

		/* Form the linear combinations */
	
number1+=1941*mother1[2]+1860*mother1[3]+1812*mother1[4]+1776*mother1[5]+
				
1492*mother1[6]+1215*mother1[7]+1066*mother1[8]+12013*mother1[9];
	
number2+=1111*mother2[2]+2222*mother2[3]+3333*mother2[4]+4444*mother2[5]+
				
5555*mother2[6]+6666*mother2[7]+7777*mother2[8]+9272*mother2[9];

		/* Save the high bits of numberi as the new carry */
	mother1[0]=number1/m16Long;
	mother2[0]=number2/m16Long;
		/* Put the low bits of numberi into motheri[1] */
	mother1[1]=m16Mask&number1;
	mother2[1]=m16Mask&number2;

		/* Combine the two 16 bit random numbers into one 32 bit */
	*pSeed=(((long)mother1[1])<<16)+(long)mother2[1];

		/* Return a double value between 0 and 1 */
	return ((double)*pSeed)/m32Double;
}


#endif