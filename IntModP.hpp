#define _CRYP_BEGIN namespace cryp {
#define _CRYP_END }
#pragma once
#include <iostream>
#include <tuple>
#include "bigint/BigInteger.hh"

_CRYP_BEGIN

template<class size_type,int p>
class IntModP
{
public:
	constexpr static int mod = p;

	IntModP(const size_type& a)
	{
		this->val = a % p;
	}

	IntModP(size_type&& a)
	{
		this->val = std::move(a) % p;
	}

	size_type operator*(const size_type& rhs)
	{
		return this->val * rhs % p;
	}

	~IntModP() = default;

	size_type val;

private:
	std::tuple< size_type, size_type, size_type> exgcd(const size_type &a, const size_type& b)
	{
		if (b == 0) 
			return std::make_tuple(1, 0, a);
		else
		{
			auto [x, y, q] = exgcd(b, a % b);
			std::swap(x, y);
			y = y - (a / b) * x;
			return std::make_tuple(x, y, q);
		}
	}

public:
	size_type number_theoretic_reciprocal()
	{
		return std::get<0>(exgcd(this->val, p)) % p;
	}
};



_CRYP_END