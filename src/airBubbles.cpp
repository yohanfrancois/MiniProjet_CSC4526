#include "airBubbles.h"

AirBubbles::AirBubbles(float x, float y) : Interactible("resources/airBubbles.png", sf::CircleShape(50.f), 3.f, x, y) {}

void AirBubbles::effect(EventManager* Eventmanager)
{
	Eventmanager->addTime(bonusTime);
}

void AirBubbles::update(sf::Time deltaTime) {
//nothing to update yet 
}