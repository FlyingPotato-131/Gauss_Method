#include "fraction.hpp"

int main(){
	fraction q1 = fraction(-6, 14);
	// fraction q2 = fraction(9, 3);
	// fraction q3 = frac(5);
	fraction q3;
	// std::cin >> q3;
	fraction q4 = q3;
	// q1 /= q2;
	std::cout << simplify(q1) << std::endl;
}