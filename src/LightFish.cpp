#include "LightFish.h"
#include <iostream>
#include "Game.h"

LightFish::LightFish(float x, float y) : Interactible("resources/littleLight.png", sf::CircleShape(50.f), 0.3f, x, y)
{
    // plus rien 
}

void LightFish::effect(EventManager* eventManager)
{
    std::cout << "lightFish effect" << std::endl;
    eventManager->endGameEaten(hitBoxInteractible.getPosition());
}

void LightFish::update(sf::Time deltaTime)
{
    //manger des sharks et disparaitre ?
}

bool LightFish::isLightSource() {
    return true;
}