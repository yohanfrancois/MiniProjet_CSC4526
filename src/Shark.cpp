#include "Shark.h"
#include <iostream>
#include "Game.h"

void Shark::effect(EventManager* eventManager)
{
	std::cout << "Shark effect" << std::endl;
	eventManager->endGame();
}

void Shark::update()
{

	if (hitBoxInteractible.getPosition().x > SCREEN_WIDTH - hitBoxInteractible.getRadius() || hitBoxInteractible.getPosition().x < 0 + hitBoxInteractible.getRadius())
	{
		speed = -speed;
	}
	hitBoxInteractible.move(speed);
}

float Shark::trueHitBox() {
	return hitBoxBonus + hitBoxInteractible.getRadius();
}