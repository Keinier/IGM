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
#ifndef __IEMATH_CORE_HPP__
#define __IEMATH_CORE_HPP__
#include <cmath>
#include <IEMath\core\iemath_core.hpp>
#include <IEAtom.h>


/*
class coordinate_system
{
public:
	coordinate_system(){}
	virtual toCylindrical(){}
	virtual toSpherical(){}
	virtual toCartesianLH(){}
	virtual toCartesianRH(){}


};
*/
template<class TReal>class IEMath
{
public:
	
	static TReal ACos (TReal fValue){return (TReal)acos((TReal)fValue);}
	static TReal ASin (TReal fValue){return (TReal)asin((TReal)fValue);}
	static TReal ATan (TReal fValue){return (TReal)atan((TReal)fValue);}

	static TReal ATan2 (TReal fY, TReal fX){return (TReal)atan2((TReal)fY,(TReal)fX);}

	static TReal Ceil (TReal fValue){return (TReal)ceil((TReal)fValue);}
	static TReal Cos (TReal fValue){return (TReal)cos((TReal)fValue);}
	static TReal Exp (TReal fValue){return (TReal)exp((TReal)fValue);}
	static TReal FAbs (TReal fValue){return (TReal)abs((TReal)fValue);}
	static TReal Floor (TReal fValue){return (TReal)floor((TReal)fValue);}
	static TReal FMod (TReal fX, TReal fY){return (TReal)fmod((TReal)fX,(TReal)fY);}
	static TReal InvSqrt (TReal fValue){return (TReal)1/sqrt((TReal)fValue);}
	static TReal Log (TReal fValue){return (TReal)log((TReal)fValue);}
	static TReal Pow (TReal fBase, TReal fExponent){return (TReal)pow((TReal) fBase, (TReal) fExponent);}
	static TReal Sin (TReal fValue){return (TReal)sin((TReal)fValue);}
	static TReal Sqr (TReal fValue){return (TReal)((TReal)fValue*fValue);}
	static TReal Sqrt (TReal fValue){return (TReal)sqrt((TReal)fValue);}
	static TReal Tan (TReal fValue){return (TReal)tan((TReal)fValue);}

	// constants
	static const TReal EPSILON ;
	static const TReal MAX_REAL;
	static const TReal PI;
	static const TReal TWO_PI;
	static const TReal HALF_PI;
	static const TReal INV_PI;
	static const TReal INV_TWO_PI;
	static const TReal DEG_TO_RAD;
	static const TReal RAD_TO_DEG;


	// a few function

	static I32 Sign (I32 iValue)
	{
		return -(iValue);
	}
	static TReal Sign (TReal fValue)
	{
		return -(iValue);
	}
	static TReal UnitRandom (U32 uiSeed = 0){ return 0;}
	static TReal SymmetricRandom (U32 uiSeed = 0){return 0;}
	static TReal IntervalRandom (TReal fMin, TReal fMax,U32 uiSeed = 0){return 0;}


};


#endif //__IEMATH_CORE_HPP__