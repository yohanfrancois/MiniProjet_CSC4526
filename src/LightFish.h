#pragma once
#ifndef LIGHTFISH_H
#define LIGHTFISH_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include <memory>

class LightFish : public Interactible
{
public:
	LightFish(float x, float y);
	void effect(EventManager* eventManager) override;
	void update() override;
	bool isLightSource() override;

private:
	sf::Texture littleLightTexture;
	bool unSeen = false;
	float growthFactor = 1.1;
	bool Growing = false;
};

#endif // !LIGHTFISH_H