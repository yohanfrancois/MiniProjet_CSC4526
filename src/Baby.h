#pragma once
#ifndef BABY_H
#define BABY_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <SFML/Audio.hpp>

class Baby : public Interactible
{
public:
	Baby(float x, float y);
	void effect(EventManager* eventManager) override;
	void update(sf::Time deltaTime) override;
	bool isLightSource() override;
	float trueHitBox() override;

private:
	sf::Texture littleLightTexture;
	bool unSeen = false;
	float hitBoxBonus = 20.f;

	sf::SoundBuffer buffer;
	sf::Sound babySound;
};

#endif // !BABY_H