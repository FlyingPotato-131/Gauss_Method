#pragma once
#include <iostream>

struct fraction{
	int num;
	int den;
};

void printfrac(fraction q){
	if(q.den != 1)
		std::cout << q.num << "/" << q.den;
	else
		std::cout << q.num;
}

fraction frac(int num, int den){
	return {num, den};
}

int absv(int a){
	return a >= 0 ? a : -a;
}

int gcd(int a, int b){
	if(a == 0)
		return b;
	if(b == 0)
		return a;
	if(a % 2 == 0 && b % 2 == 0)
		return 2 * gcd(a/2, b/2);
	if(a % 2 == 0)
		return gcd(a/2, b);
	if(b % 2 == 0)
		return gcd(a, b/2);
	return gcd(absv(a - b), std::min(a, b));
}

fraction simplify(fraction q){
	int n = gcd(q.num, q.den);
	return {q.num / n, q.den / n};
}

fraction operator+(fraction q1, fraction q2){
	return simplify({q1.num * q2.den + q2.num * q1.den, q1.den * q2.den});
}

fraction operator-(fraction q){
	return {-q.num, q.den};
}

fraction operator-(fraction q1, fraction q2){
	return q1 + (-q2);
}

fraction operator*(fraction q1, fraction q2){
	return simplify({q1.num * q2.num, q1.den * q2.den});
}

fraction operator/(fraction q1, fraction q2){
	return simplify({q1.num * q2.den, q1.den * q2.num});
}