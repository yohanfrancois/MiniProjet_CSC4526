#pragma once
#ifndef INTERACTIBLE_H
#define INTERACTIBLE_H

#include <SFML/Graphics.hpp>
#include <string>

class Interactible
{
public:
	Interactible(const std::string& texture_path, sf::CircleShape& hitbox, float reactiontime);
	void draw(sf::RenderWindow& window) const;
	void update();
private:
	sf::CircleShape hitBoxInteractible;
	float reactionTime;
	sf::Texture inter_Texture;
};

#endif // INTERACTIBLE_H