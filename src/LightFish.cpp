#include "LightFish.h"
#include <iostream>

LightFish::LightFish(float x, float y) : Interactible("resources/Ponyo.png", sf::CircleShape(50.f), 1.f, x, y)
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
    eventManager->winLevel();
}

void LightFish::update()
{
    if (isVisible() && unSeen) {
        hitBoxInteractible.setTexture(&inter_Texture);
        hitBoxInteractible.setTextureRect(sf::IntRect(0, 0, inter_Texture.getSize().x, inter_Texture.getSize().y));
        unSeen = false;
    }
    else if (!isVisible() && !unSeen) {
        hitBoxInteractible.setTexture(&littleLightTexture);
        hitBoxInteractible.setTextureRect(sf::IntRect(0, 0, littleLightTexture.getSize().x, littleLightTexture.getSize().y));
        unSeen = true;
    }
}

bool LightFish::isLightSource() {
    return true;
}