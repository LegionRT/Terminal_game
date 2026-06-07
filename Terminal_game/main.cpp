#include <iostream>
#include "location.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Location location(1);
	location.init();
	return 0;
}