#include "Shark.h"
#include <iostream>
#include "Game.h"

void Shark::effect(EventManager* eventManager)
{
	std::cout << "Shark effect" << std::endl;
	eventManager->endGame();
}

void Shark::update(sf::Time deltaTime)
{

	if (hitBoxInteractible.getPosition().x > SCREEN_WIDTH - 2*hitBoxInteractible.getRadius() || hitBoxInteractible.getPosition().x < 0)
	{
		speed = -speed;
	}
	hitBoxInteractible.move(speed);
}

float Shark::trueHitBox() {
	return hitBoxBonus + hitBoxInteractible.getRadius();
}