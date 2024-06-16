#include "Interactible.h"
#include <iostream>

using namespace std;

Interactible::Interactible(const std::string& texture_path, const sf::CircleShape& hitbox, float time, float x, float y)
	: hitBoxInteractible(hitbox),
	reactionTime(time)
{
	if (!inter_Texture.loadFromFile(texture_path))
	{
		std::cerr << "Failed to load texture from " << texture_path << std::endl;
	}
	else
	{
		hitBoxInteractible.setTexture(&inter_Texture);
	}

	hitBoxInteractible.setPosition(x, y);
}

void Interactible::draw(sf::RenderWindow& window) const
{
	window.draw(hitBoxInteractible);
}

void Interactible::updateVisibility(sf::CircleShape& lightCircle)
{
	sf::Vector2f hitboxPosition = hitBoxInteractible.getPosition();
	sf::Vector2f lightPosition = lightCircle.getPosition();
	float hitboxRadius = hitBoxInteractible.getRadius();

	float distance = sqrt(pow(hitboxPosition.x+hitboxRadius - lightPosition.x, 2) + pow(hitboxPosition.y + hitboxRadius - lightPosition.y, 2));
	bool currentlyVisible = distance <= trueHitBox();
	
	if (currentlyVisible)
	{
		if (!mIsVisible)
		{
			visibilityClock.restart();
		}
	}
	else {
		visibilityClock.restart();
	}
	mIsVisible = currentlyVisible;
}

bool Interactible::isVisible() const
{
	return mIsVisible;
}

float Interactible::getReactionTime() const
{
	return reactionTime;
}


sf::Clock Interactible::getVisibilityClock() const
{
	return visibilityClock;
}

void Interactible::resetVisibilityClock()
{
	visibilityClock.restart();
}

sf::CircleShape Interactible::getHitBox() const{
	return hitBoxInteractible;
}

void Interactible::changeTexture(sf::Texture texture)
{
	hitBoxInteractible.setTexture(&texture);
}

float Interactible::trueHitBox()
{
	return hitBoxInteractible.getRadius();
}