#pragma once
#ifndef AIRBUBBLES_H
#define AIRBUBBLES_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

class AirBubbles : public Interactible
{
public:
	AirBubbles(float x, float y);
	void effect(EventManager* eventManager) override;
	void update(sf::Time deltaTime) override;
private:
	float bonusTime = 5;
};

#endif // !AIRBUBBLES_H