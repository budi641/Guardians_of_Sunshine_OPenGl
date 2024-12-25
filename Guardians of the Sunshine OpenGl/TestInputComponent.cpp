#include "TestInputComponent.h"
#include <iostream>

void TestInputComponent::On_W_KeyPressed()
{
	std::cout << "W is pressed" << std::endl;
}

void TestInputComponent::On_W_KeyReleased()
{
	std::cout << "W is Released" << std::endl;
}
