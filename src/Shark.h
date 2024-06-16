#pragma once
#ifndef SHARK_H
#define SHARK_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class Shark : public Interactible
{
public:
	Shark(float x, float y) : Interactible(static_cast<std::string>("resources/shark.png"), sf::CircleShape(50.f), 1.5f, x, y) { std::cout << "Shark spawn" << std::endl; };
	void effect(EventManager* eventManager) override;
	void update(sf::Time deltaTime) override;
	float trueHitBox() override;
	sf::Vector2f speed{ 1.f, 0.f }; //public seulement pour les tests Todo getter si modif ailleurs!

private:
	
	float hitBoxBonus = 90.f;
};

#endif // !SHARK_H