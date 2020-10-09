// Cryptographic-Analysis-Program.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "IntModP.hpp"
#include "bigint/BigInteger.hh"
#include "bigint/BigIntegerUtils.hh"
#include "cyclical.hh"
#include "IntModP.hpp"
#include "ELGamal.hpp"

using namespace std;
using namespace cryp;

void textIntModP();

int main()
{
	textIntModP();
	textELGamal();
}


void textIntModP()
{
	BigInteger a = stringToBigInteger("114514191981011451411451419198101");
	cryp::IntModP<BigInteger> b(2, a);
	cryp::IntModP<BigInteger> c(6, a);
	cryp::IntModP<BigInteger> t = pow(b, a);
	std::cout << c << " * " << c.number_theoretic_reciprocal() <<
		" = " << c * c.number_theoretic_reciprocal() << std::endl;
	auto t_c = t / c;
	std::cout << t << " = " << t_c << " * " << c << " = " << t_c * c << std::endl;
}
