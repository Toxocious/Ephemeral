#include "Core.h"

#include <iostream>

#include <utils/timer.h>
#include <utils/time.h>

#include <glm/common.hpp>

namespace Core
{
	void PrintHelloWorld()
	{
		auto t = glm::abs(1.0f);

		Ephemeral::Timer timer;
		std::cout << "Hello World!\n";
		std::cout << "Time elapsed: " << timer.ElapsedMillis() << "ms" << std::endl;
		std::cout << "Current time: " << Ephemeral::Time::GetTime() << std::endl;
		std::cin.get();
	}
}
