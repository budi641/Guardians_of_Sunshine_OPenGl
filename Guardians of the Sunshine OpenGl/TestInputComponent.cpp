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

void TestInputComponent::On_W_KeyHeld()
{
	std::cout << "W is Held" << std::endl;
}

void TestInputComponent::On_S_KeyPressed()
{
	std::cout << "S is pressed" << std::endl;
}

void TestInputComponent::On_S_KeyReleased()
{
	std::cout << "S is Released" << std::endl;
}

void TestInputComponent::On_S_KeyHeld()
{
	std::cout << "S is Held" << std::endl;
}