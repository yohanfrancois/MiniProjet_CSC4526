#pragma once
#ifndef SHARK_H
#define SHARK_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Shark : public Interactible
{
public:
	Shark(float x, float y) : Interactible(static_cast<std::string>("resources/shark.png"), sf::CircleShape(50.f), 1.f, x, y) {};
	void effect() override;
};

#endif // !SHARK_H