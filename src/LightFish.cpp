#include "LightFish.h"
#include <iostream>
#include "Game.h"

LightFish::LightFish(float x, float y) : Interactible("resources/lightFish.png", sf::CircleShape(50.f), 0.3f, x, y)
{
    // Chargement de la texture littleLight
    if (!littleLightTexture.loadFromFile("resources/littleLight.png")) {
        std::cout << "Error: Can't find littleLight.png" << std::endl;
    }
    hitBoxInteractible.setTexture(&littleLightTexture);
    hitBoxInteractible.setTextureRect(sf::IntRect(0, 0, littleLightTexture.getSize().x, littleLightTexture.getSize().y));

}

void LightFish::effect(EventManager* eventManager)
{
    std::cout << "lightFish effect" << std::endl;
    eventManager->endGameEaten(hitBoxInteractible.getPosition());
}

void LightFish::update(sf::Time deltaTime)
{

}

bool LightFish::isLightSource() {
    return true;
}