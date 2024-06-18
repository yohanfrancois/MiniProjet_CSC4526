#include "Baby.h"
#include <iostream>

Baby::Baby(float x, float y) : Interactible("resources/Ponyo.png", sf::CircleShape(50.f), 3.f, x, y)
{
    // Chargement de la texture littleLight
    if (!littleLightTexture.loadFromFile("resources/littleLight.png")) {
        std::cout << "Error: Can't find littleLight.png" << std::endl;
    }
    hitBoxInteractible.setTexture(&littleLightTexture);
    hitBoxInteractible.setTextureRect(sf::IntRect(0, 0, littleLightTexture.getSize().x, littleLightTexture.getSize().y));

}

void Baby::effect(EventManager* eventManager)
{
	std::cout << "Baby effect" << std::endl;
	eventManager->winLevel();
}

void Baby::update(sf::Time deltaTime)
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

bool Baby::isLightSource() {
    return unSeen;
}


float Baby::trueHitBox() {
    return hitBoxBonus + hitBoxInteractible.getRadius();
}