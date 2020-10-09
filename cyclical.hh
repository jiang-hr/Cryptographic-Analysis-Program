//Some operations in a loop group.
#define _CRYP_BEGIN namespace cryp {
#define _CRYP_END }
#pragma once
#include <iostream>

_CRYP_BEGIN
// A is a member of the cyclic group, and B is the power.
template<class cycle, class size_type>
cycle pow(cycle a, size_type b)
{
	cycle res = a.unit();
	for (; b > 0;)
	{
		if (b % 2 == 1)
			res *= a;
		a *= a ;
		b /= 2;
	}
	return res;
}

_CRYP_END