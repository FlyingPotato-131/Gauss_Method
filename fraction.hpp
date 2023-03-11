#pragma once
#include <iostream>

struct fraction{
	int num;
	int den;
};

std::ostream &printfrac(std::ostream &out, fraction q){
	if(q.den != 1)
		std::cout << q.num << "/" << q.den;
	else
		std::cout << q.num << " " << " ";
	return out;
}

std::ostream &operator<<(std::ostream &out, fraction q){
	return printfrac(out, q);
}

// std::istream &operator>>(std::istream &in, fraction q){
// 	float f;
// 	in >> f;

// }

// float contfrac(float f){
// 	int n = static_cast<int>(f);
// 	float df = f - n;
// 	if(df == 0)
// 		return n;
// 	next = static_cast<int>(1/df);
// 	return n +
// }

// fraction frac(float f){
// 	int n = static_cast<int>(f);
// 	float df = f - n;
// 	if(df == 0)
// 		return {n, 1};
// 	int next = static_cast<int>(1/df);
// 	return frac(n, 1) + frac(1, 1)/frac(next, 1);
// }

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
	if(q.den < 0){
		q.num = -q.num;
		q.den = -q.den;
	}
	int n = gcd(absv(q.num), q.den);
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

fraction operator/=(fraction &q1, fraction q2){
	q1 = q1 / q2;
	return q1;
}

fraction operator-=(fraction &q1, fraction q2){
	q1 = q1 - q2;
	return q1;
}

bool operator==(fraction q1, fraction q2){
	q1 = simplify(q1);
	q2 = simplify(q2);
	return q1.num == q2.num && q1.den == q2.den;
}

bool operator!=(fraction q1, fraction q2){
	return !(q1 == q2);
}

fraction frac(float f){
	int n = 10;
	while(f * 10 != int(f*10)){
		f *= 10;
		n *= 10;
	}
	return simplify(frac(f * 10, n));
}

std::istream &operator>>(std::istream &in, fraction &q){
	float f;
	in >> f;
	q = frac(f);
	return in;
}

// fraction frac(float f){
// 	int n = int(f);
// 	float df = f - n;
// 	// std::cout << n << " " << df << std::endl;
// 	if(df == 0)
// 		return frac(n, 1);
// 	float next = 1/df;
// 	return frac(n, 1) + frac(1, 1)/frac(next);
// }