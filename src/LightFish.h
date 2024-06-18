#pragma once
#ifndef LIGHTFISH_H
#define LIGHTFISH_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Game.h"

class LightFish : public Interactible
{
public:
	LightFish(float x, float y);
	void effect(EventManager* eventManager) override;
	void update(sf::Time deltaTime) override;
	bool isLightSource() override;

private:
	sf::Texture littleLightTexture;
	bool unSeen = false;
};

#endif // !LIGHTFISH_H