#include "Utils.h"

sf::Vector2f normalize(const sf::Vector2f& vector) {
    if (float length = std::sqrt(vector.x * vector.x + vector.y * vector.y); length != 0) { // On divise pas par 0 si vecteur nul
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    return vector; 
}