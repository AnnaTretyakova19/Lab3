#include <iostream>
#include <chrono>
#include "Header.h"

using namespace std;



int main()
{
	polinomial a("111");
	polinomial b("1");
	polinomial c("10100000000000000000000000000000111100000000000000000000000000001110");
	
	

	
	a.print();
	b.print();
	c.print();
	polinomial d;
	d = b + a;
	d.print();
	
}