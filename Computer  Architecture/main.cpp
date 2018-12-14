#include <iostream>
#include <chrono>
#include <string>
#include "Lab 1/benchmark.cpp"

////////////////////////////////////////////////////////////////////////////////

using namespace std::chrono;

int main() {
	std::cout << "int + per sec:	   \t" << 
		lab1::addsPerSec<int>() << std::endl;
	std::cout << "int - per sec:       \t" << 
		lab1::diffsPerSec<int>() << std::endl;
	std::cout << "int * per sec:       \t" << 
		lab1::multsPerSec<int>() << std::endl;
	std::cout << "int / per sec:       \t" << 
		lab1::divsPerSec<int>() << std::endl;

	std::cout << std::endl;

	std::cout << "long long + per sec: \t" << 
		lab1::addsPerSec<long long>() << std::endl;
	std::cout << "long long - per sec: \t" << 
		lab1::diffsPerSec<long long>() << std::endl;
	std::cout << "long long * per sec: \t" << 
		lab1::multsPerSec<long long>() << std::endl;
	std::cout << "long long / per sec: \t" << 
		lab1::divsPerSec<long long>() << std::endl;

	std::cout << std::endl;

	std::cout << "double + per sec:    \t" << 
		lab1::addsPerSec<double>() << std::endl;
	std::cout << "double - per sec:    \t" << 
		lab1::diffsPerSec<double>() << std::endl;
	std::cout << "double * per sec:    \t" << 
		lab1::multsPerSec<double>() << std::endl;
	std::cout << "double / per sec:    \t" << 
		lab1::divsPerSec<double>() << std::endl;

	std::cout << std::endl;

	std::cout << "float + per sec:     \t" << 
		lab1::addsPerSec<float>() << std::endl;
	std::cout << "float - per sec:     \t" <<
		lab1::diffsPerSec<float>() << std::endl;
	std::cout << "float * per sec:     \t" << 
		lab1::multsPerSec<float>() << std::endl;
	std::cout << "float / per sec:     \t" << 
		lab1::divsPerSec<float>() << std::endl;

	std::cout << std::endl;

	system("pause");
}