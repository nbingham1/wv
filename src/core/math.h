/*
 * math.h
 *
 *  Created on: Sep 25, 2014
 *      Author: nbingham
 */

#ifndef math_h
#define math_h

#include <math.h>

namespace core
{

#define m_pi 3.14159265358979323
#define m_e 2.718281828
#define m_epsilon 0.000001

#define degtorad(a) m_pi*a/180.0
#define radtodeg(a) 180.0*a/m_pi

unsigned int count_ones(unsigned int x);
unsigned int count_zeros(unsigned int x);

template <class type>
type powi(type base, int exp)
{
    type result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

int log2i(unsigned long long value);

template <class type>
type abs(type &t)
{
	return (t < 0 ? -t : t);
}

template <class type>
type min(type t1, type t2)
{
	return (t1 < t2 ? t1 : t2);
}

template <class type>
type max(type t1, type t2)
{
	return (t1 < t2 ? t2 : t1);
}

template <class type>
type clamp(type t, type left, type right)
{
	return max(min(t, right), left);
}

template <class type>
type median(type t1, type t2, type t3)
{
	if (t1 < t2)
	{
		if (t2 < t3)
			return t2;
		else if (t3 < t1)
			return t1;
		else
			return t3;
	}
	else
	{
		if (t1 < t3)
			return t1;
		else if (t3 < t2)
			return t2;
		else
			return t3;
	}
}

bool is_even(int i);
bool is_odd(int i);

}

#endif
