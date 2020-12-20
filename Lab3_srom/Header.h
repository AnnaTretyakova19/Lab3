#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

class polinomial {

private:

	typedef unsigned int data_t;

	static const int SIZE = 16;
	data_t* intlong;

public:
	
	polinomial() {
		intlong = new data_t[SIZE];
		for (int i = 0; i < SIZE; i++) {
			intlong[i] = 0;
		}
	};

	polinomial(string _str) : polinomial()
	{
		int lastbit = 31;
		for (int i = 0; i <= (_str.size() / 32); i++) {
			if (_str.size() / 32 == i) {
				lastbit = _str.size() % 32;
			}
			for (int j = 0; j < lastbit; j++) {
				if (_str[_str.size() - 1 - j - 32 * i] == '1') {
					intlong[i] += pow(2, j);
				}
			}
		}
	}

	polinomial(const polinomial& _polinomial) {
		intlong = new data_t[SIZE];
		for (int i = 0; i < SIZE; ++i) {
			intlong[i] = _polinomial.intlong[i];
		}
	}

	~polinomial() {
		delete[] intlong;
	}
	
	operator string() const {
		string snum;
		for (int i = SIZE-1; i >= 0; --i) {
			for (int j = 31; j >= 0; --j) {
				snum += "01"[(intlong[i] >> j) & 1];
			}				
		}
		for (int i = 0; i < 22;i++) {
			snum[i] = 0;
		}
		return snum;
	}

	polinomial& operator = (const polinomial& _polinomial) {
		for (int i = 0; i < SIZE; ++i) {
			intlong[i] = _polinomial.intlong[i];
		}
		return *this;
	}

	polinomial operator + (const polinomial& b) const {
		polinomial res;
		for (int i = 0; i < SIZE; i++) {
			res.intlong[i] = intlong[i] ^ b.intlong[i];
		}
		return res;
	}

	polinomial operator * (const polinomial& b) const {
		polinomial res;
		for (int i = 0; i < SIZE; i++) {
			res.intlong[i] = intlong[i] ^ b.intlong[i];
		}
		return res;
	}

	void print() const
	{
		cout << string(*this) << '\n';
	}
};