#include <chrono>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////

namespace lab1 {
	template<typename T>
	unsigned long long addsPerSec(unsigned long long ops = 3e8) {
		T a = static_cast <T>(3), b = static_cast <T>(2),
		  c = static_cast <T>(1);

		auto start = std::chrono::steady_clock::now();
		for (int i = 1; i <= ops; ++i) {
			a = b + c;
			b = a + c;
			c = a + b;

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);
		}
		auto pre_end = std::chrono::steady_clock::now();

		for (int i = 1; i <= ops; ++i) {
			a = b;
			b = a;
			c = c;

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);
		}

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed_sec = (pre_end - start) - 
													(end - pre_end);
		return static_cast<unsigned long long>(ops / elapsed_sec.count() * 3);
	}

	template<typename T>
	unsigned long long diffsPerSec(unsigned long long ops = 3e8) {
		T a = static_cast <T>(3), b = static_cast <T>(2),
		  c = static_cast <T>(1);

		auto start = std::chrono::steady_clock::now();
		for (int i = 1; i <= ops; ++i) {
			a = b - c;
			b = a - c;
			c = a - b;

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);
		}
		auto pre_end = std::chrono::steady_clock::now();

		for (int i = 1; i <= ops; ++i) {
			a = a;
			b = b;
			c = c;

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);
		}

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed_sec = (pre_end - start) -
			(end - pre_end);
		return static_cast<unsigned long long>(ops / elapsed_sec.count() * 3);
	}

	template<typename T>
	unsigned long long multsPerSec(unsigned long long ops = 3e8) {
		T a = static_cast <T>(3), b = static_cast <T>(2),
		  c = static_cast <T>(1);

		auto start = std::chrono::steady_clock::now();
		for (int i = 1; i <= ops; ++i) {
			a = b * c;
			b = a * c;
			c = a * b;

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);
		}
		auto pre_end = std::chrono::steady_clock::now();

		for (int i = 1; i <= ops; ++i) {
			a = a;
			b = b;
			c = c;

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);
		}

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed_sec = (pre_end - start) -
			(end - pre_end);
		return static_cast<unsigned long long>(ops / elapsed_sec.count() * 3);
	}

	template<typename T>
	unsigned long long divsPerSec(unsigned long long ops = 3e8) {
		T a = static_cast <T>(3), b = static_cast <T>(2),
		  c = static_cast <T>(1);

		auto start = std::chrono::steady_clock::now();
		for (int i = 1; i <= ops; ++i) {

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);

			a = b / c;
			b = a / c;
			c = a / a;

		}
		auto pre_end = std::chrono::steady_clock::now();

		for (int i = 1; i <= ops; ++i) {
			a = a;
			b = b;
			c = c;

			a = static_cast<T>(i);
			b = static_cast<T>(i);
			c = static_cast<T>(i);
		}

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed_sec = (pre_end - start) -
			(end - pre_end);
		return static_cast<unsigned long long>(ops / elapsed_sec.count() * 3);
	}
}				
