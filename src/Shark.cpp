#include "Shark.h"
#include <iostream>

void Shark::effect(EventManager* eventManager)
{
	std::cout << "Shark effect" << std::endl;
	eventManager->endGame();
}