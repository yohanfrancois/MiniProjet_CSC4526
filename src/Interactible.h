#pragma once
#ifndef INTERACTIBLE_H
#define INTERACTIBLE_H

#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include <string>

class Interactible
{
public:
	Interactible(const std::string& texture_path, const sf::CircleShape& hitbox, float time, float x, float y);
	virtual ~Interactible() = default;
	void draw(sf::RenderWindow& window) const;
	virtual void update() = 0;
	virtual void effect(EventManager* eventManager) = 0;
	virtual bool isLightSource() { return false; };
	void updateVisibility(sf::CircleShape& lightCircle);
	bool isVisible() const;
	float getReactionTime() const;
	sf::Clock getVisibilityClock() const;
	void resetVisibilityClock();
	sf::CircleShape getHitBox() const;
	void changeTexture(sf::Texture texture);
	virtual float trueHitBox();
protected:
	sf::CircleShape hitBoxInteractible;
	float reactionTime;
	sf::Texture inter_Texture;
	bool mIsVisible = false;
	sf::Clock visibilityClock;
};

#endif // INTERACTIBLE_H