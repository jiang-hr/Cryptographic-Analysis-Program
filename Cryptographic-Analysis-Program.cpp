// Cryptographic-Analysis-Program.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "IntModP.hpp"
#include "bigint/BigInteger.hh"
#include "bigint/BigIntegerUtils.hh"

using namespace std;

int main()
{
	auto a = stringToBigInteger("11451419198101145141145141919810");
	cryp::IntModP<BigInteger, 735001> b(a);
	cout << a << " * " << b.number_theoretic_reciprocal() 
		<< " % " << b.mod << " = " << b * b.number_theoretic_reciprocal() % b.mod << endl;
}

