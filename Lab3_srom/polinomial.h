#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

using namespace std;

class polinomial {

private:

	constexpr static int M = 491;

	bitset<M * 2> intlong;

	int highbit() const {
		for (int i = M * 2 - 1; i >= 0; --i) {
			if (intlong[i]) {
				return i;
			}
		}
		return -1;
	}

public:

	const static polinomial G;

	polinomial() = default;
	polinomial(const bitset<M * 2>& _intlong)
	{
		intlong = _intlong;
	}
	polinomial(string str) : polinomial(bitset<M * 2>(str)) {}
	polinomial(const polinomial&) = default;
	polinomial& operator = (const polinomial&) = default;
	~polinomial() = default;

	bool operator == (const polinomial& n) const {
		return intlong == n.intlong;
	}

	polinomial& operator <<= (int n) {
		intlong <<= n;
		return *this;
	}
	polinomial operator << (int n) const {
		return polinomial(*this) <<= n;
	}
	polinomial& operator >>= (int n) {
		intlong >>= n;
		return *this;
	}
	polinomial operator >> (int n) const {
		return polinomial(*this) >>= n;
	}
	polinomial& operator += (const polinomial& n) {
		intlong ^= n.intlong;
		return *this;
	}
	polinomial operator + (const polinomial& n) const {
		return polinomial(*this) += n;
	}
	polinomial& operator *= (const polinomial& n) {
		polinomial result;
		for (int i = 0; i < M; ++i) {
			if (n.intlong[i]) {
				result += *this;
			}
			*this <<= 1;
		}
		for (int i = result.highbit(); i >= M; i = result.highbit()) {
			result += G << (i - M);
		}
		return *this = result;
	}
	polinomial operator * (const polinomial& b) const {
		return polinomial(*this) *= b;
	}

	bool trace() const {
		return intlong.count() & 1;
	}
	polinomial sqr() const {
		return *this * *this;
	}
	polinomial inverse() const {
		const static polinomial inverter = polinomial(bitset<M * 2>(1)).flip();
		return pow(*this, inverter);
	}
	polinomial flip() const {
		return polinomial((*this << M).intlong.flip() >> M);
	}

	static polinomial pow(const polinomial& a, const polinomial& b) {
		if (b.intlong.none()) {
			return bitset<M * 2>(1);
		}
		return b.intlong[0] ? pow(a, b >> 1).sqr() * a : pow(a, b >> 1).sqr();
	}

	operator string() const {
		return *this == G ? intlong.to_string().substr(M - 1) : intlong.to_string().substr(M);
	}

	friend ostream& operator << (ostream& os, const polinomial& n) {
		return os << string(n);
	}

};

const polinomial polinomial::G = polinomial("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100000000001000101");