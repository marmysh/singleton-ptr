#include "pch.h"

#include "SingletonPtr.h"

int main()
{
	SingletonPtr<double> x;
	x = 10;

	SingletonPtr<double> y = 11;

	if (x == y)
	{
		return 0;
	}
	return 1;
}

