#define _CRYP_BEGIN namespace cryp {
#define _CRYP_END }
#define _CRYP ::cryp::
#pragma once
#include <utility>
#include "bigint/BigInteger.hh"
#include "IntModP.hpp"
#include "cyclical.hh"

_CRYP_BEGIN

// The first parameter type is a cyclic group type, and the second parameter type is an integer.
template <class cycle, class size_type>
class ELGamal
{
public:

	ELGamal(const cycle& gen, size_type x)
	{
		this->g = gen;
		this->x = x;
		__generate_public_key();
	}

	inline cycle get_h()
	{
		return this->h;
	}

	// y is randomly selected and is called temporary key. M is the plaintext to be encrypted.
	std::pair<cycle, cycle> encrypt(const size_type& y, const cycle& m)
	{
		//先計算 c_{1}:=g^{y}。
		auto c_1 = _CRYP pow(this->g, y);
		auto s = _CRYP pow(this->get_h(), y);
		auto c_2 = s * m;
		return std::make_pair(c_1, c_2);
	}

	// 密文 cipher = (c_{1},c_{2})=(g^{y},m\cdot h^{y})=(g^{y},m\cdot (g^{x})^{y})
	// x為私鑰，cipher為密文對。
	static cycle decrypt(size_type x, const std::pair<cycle, cycle>& cipher)
	{
		auto s = _CRYP pow(cipher.first, x);
		return cipher.second / s;
	}

private:
	void __generate_public_key()
	{
		this->h = _CRYP pow<cycle, size_type>(g, x);
	}

private:
	//私鑰
	size_type x;
	cycle h;

public:
	//生成元g。
	cycle g;
};



void textELGamal()
{
	using cycle = _CRYP IntModP<BigInteger>;
	const BigInteger p = 13171;
	const int x = 2;
	cycle g = _CRYP IntModP<BigInteger>(BigInteger(2), p);

	ELGamal<cycle, int> a = ELGamal<cycle, int>(g, x);
	cycle m = cycle(114, p);
	std::cout << "m = " << m << " , " << m.p << std::endl;
	std::pair<cycle, cycle> ciper = a.encrypt(15, m);
	std::cout << "ciper.first = " << ciper.first << " , ciper.second = " << ciper.second << std::endl;
	cycle _m_ = ELGamal<cycle, BigInteger>::decrypt(x, ciper);
	std::cout << _m_ << std::endl;
}

_CRYP_END
