#include "Interactible.h"
#include <iostream>

Interactible::Interactible(const std::string& texture_path, sf::CircleShape& hitbox, float reactiontime)
	: hitBoxInteractible(hitbox),
	reactionTime(reactiontime)
{
	if (!inter_Texture.loadFromFile(texture_path))
	{
		std::cerr << "Failed to load texture from " << texture_path << std::endl;
	}
	else
	{
		hitBoxInteractible.setTexture(&inter_Texture);
	}
}

void Interactible::draw(sf::RenderWindow& window) const
{
	window.draw(hitBoxInteractible);
}

void Interactible::update()
{
	hitBoxInteractible.setRadius( hitBoxInteractible.getRadius()+0.01f );
}