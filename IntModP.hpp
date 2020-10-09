#define _CRYP_BEGIN namespace cryp {
#define _CRYP_END }
#pragma once
#include <iostream>
#include <tuple>
#include "bigint/BigInteger.hh"

_CRYP_BEGIN

//整数mod p循环群。
template<class size_type>
class IntModP
{
public:
	size_type p;
	size_type val;

	IntModP() = default;

	IntModP(const IntModP<size_type>& cpy) :p(cpy.p), val(cpy.val) {};

	IntModP(IntModP<size_type>&& cpy)noexcept
		:p(std::move(cpy.p)), val(std::move(cpy.val)) {};

	IntModP(const size_type& a, const size_type& p)
	{
		this->p = p;
		this->val = a % p;
	}

	IntModP(size_type&& a, const size_type& p)
	{
		this->p = p;
		this->val = std::move(a) % p;
	}

	IntModP<size_type> unit()
	{
		return IntModP(1, this->p);
	}

	IntModP<size_type>& operator =(const size_type& cpy)
	{
		this->val = cpy;
		return *this;
	}

	IntModP<size_type>& operator =(const IntModP<size_type>& cpy)
	{
		this->val = cpy.val;
		this->p = cpy.p; //bug找了5个小时
		return *this;
	}

	IntModP<size_type>& operator *(const size_type& rhs) const
	{
		return *new IntModP<size_type>(this->val * rhs, this->p);
	}

	IntModP<size_type> operator *(const IntModP<size_type>& rhs) const
	{
		return IntModP<size_type>(rhs.val * this->val, this->p);
	}

	IntModP<size_type>& operator *=(const IntModP<size_type>& rhs)
	{
		this->val *= rhs.val;
		this->val %= this->p;
		return *this;
	}

	IntModP<size_type>& operator *=(const size_type& rhs)
	{
		return this->operator*=(IntModP<size_type>(rhs, this->p));
	}

	IntModP<size_type> operator /(const size_type& rhs) const
	{
		IntModP<size_type> a(rhs, this->p);
		return this->operator/(a);
	}

	IntModP<size_type> operator /(const IntModP<size_type>& rhs) const
	{
		auto x = this->val;
		return IntModP<size_type>(rhs.number_theoretic_reciprocal() * x % p, this->p);
	}

	IntModP<size_type>& operator /=(const IntModP<size_type>& rhs)
	{
		*this = this->operator/(rhs);
		return *this;
	}

	IntModP<size_type>& operator /=(const size_type& rhs)
	{
		return this->operator/=(IntModP<size_type>(rhs, this->p));
	}


	IntModP<size_type> operator -(const IntModP<size_type>& rhs) const
	{
		return IntModP<size_type>(this->val - rhs->val, this->p);
	}


	~IntModP() = default;

private:
	std::tuple<size_type, size_type, size_type> exgcd(const size_type& a, const size_type& b) const
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
	size_type number_theoretic_reciprocal() const
	{
		return std::get<0>(exgcd(this->val, p)) % p;
	}
};

_CRYP_END

template<class size_type>
std::ostream& operator <<(std::ostream& os, const cryp::IntModP<size_type>& x) {
	std::cout << x.val;
	return os;
}

