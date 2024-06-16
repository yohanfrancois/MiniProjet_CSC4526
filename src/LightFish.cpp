#include "LightFish.h"
#include <iostream>
#include "Game.h"

LightFish::LightFish(float x, float y) : Interactible("resources/lightFish.png", sf::CircleShape(50.f), 0.2f, x, y)
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
    eventManager->endGame();
}

void LightFish::update()
{
    if (Growing) {
        hitBoxInteractible.setScale(hitBoxInteractible.getScale() * growthFactor);
        
    }
    if (isVisible() && unSeen) {
        hitBoxInteractible.setTexture(&inter_Texture);
        hitBoxInteractible.setTextureRect(sf::IntRect(0, 0, inter_Texture.getSize().x, inter_Texture.getSize().y));
        unSeen = false;

        Growing = true;
        std::cout << "oui";
        if (hitBoxInteractible.getPosition().x > SCREEN_WIDTH / 2) {
            hitBoxInteractible.setScale(-1.f, 1.f);
        }
    }
    else if (!isVisible() && !unSeen) {
        hitBoxInteractible.setTexture(&littleLightTexture);
        hitBoxInteractible.setTextureRect(sf::IntRect(0, 0, littleLightTexture.getSize().x, littleLightTexture.getSize().y));
        unSeen = true;
    }
}

bool LightFish::isLightSource() {
    return unSeen;
}