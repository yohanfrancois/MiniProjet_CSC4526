#pragma once
#ifndef BABY_H
#define BABY_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Baby : public Interactible
{
public:
	Baby(float x, float y);
	void effect(EventManager* eventManager) override;
	void update() override;
	bool isLightSource() override;
	float trueHitBox() override;

private:
	sf::Texture littleLightTexture;
	bool unSeen = false;
	float hitBoxBonus = 20.f;
};

#endif // !BABY_H