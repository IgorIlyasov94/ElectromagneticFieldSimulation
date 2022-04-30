#include "Main.h"

int main()
{
	std::cout << Math::Integration::GaussChebychev([](double x) {return 1.0; }, 0.0, 2.0);

	return 0;
}
