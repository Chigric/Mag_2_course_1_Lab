#include "cubatureRules.h"


namespace SundayWork {

MaxDouble CubatureRules::Trapezoidal(MaxDouble a, MaxDouble b, SpecFunc func)
{
	return ((b - a) / 2 ) * (func(a) + func(b));
}

MaxDouble CubatureRules::Simpson(MaxDouble a, MaxDouble b, SpecFunc func)
{
	return ((b - a) / 3) * (func(a) + 4*func((a+b)/2) + func(b));
}

MaxDouble CubatureRules::Simpson_3by8(MaxDouble a, MaxDouble b, SpecFunc func) // Simpson's 3/8
{
	return ((b-a) * 3/8)
			* (func(a) + 3*func((b-a) * 1/3) + 3*func((b-a) * 2/3) + func(b));
}

}
