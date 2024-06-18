#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>

#include "Shark.h"
#include "Baby.h"
#include "LightFish.h"
#include "Game.h"

// Constructeurs

TEST(Shark, Constructor) {
    float x = 100.0f;
    float y = 150.0f;

    std::unique_ptr<Shark> shark = std::make_unique<Shark>(x, y);

    EXPECT_EQ(shark->getHitBox().getPosition().x, x);
    EXPECT_EQ(shark->getHitBox().getPosition().y, y);
    EXPECT_NE(shark->getHitBox().getTexture(), nullptr);
}

TEST(Shark, Rebound) {
    // Le spawn offset est de sorte à ce que les hitbox les plus grosses dont celle du requin réussissent ce test (mais ça m'embête d'aller le chercher dans game), 2*rayon max 100.C'est l'endroit oû l'ont fait spawn les requins le plus à droite
    // On ne teste que le côté droit
    float offset = 100;
    float x = SCREEN_WIDTH - 1 - offset;
    float y = 150.0f;

    std::unique_ptr<Shark> shark = std::make_unique<Shark>(x, y);

    EXPECT_EQ(shark->getHitBox().getPosition().x, x);
    EXPECT_EQ(shark->getHitBox().getPosition().y, y);
    EXPECT_NE(shark->getHitBox().getTexture(), nullptr);

    shark->update(sf::seconds(2));
    EXPECT_EQ(shark->getHitBox().getPosition().x -2* shark-> speed , x);
    EXPECT_EQ(shark->getHitBox().getPosition().y, y);
}


TEST(LightFish, Constructor) {
    float x = 100.0f;
    float y = 150.0f;

    std::unique_ptr<LightFish> lightfish = std::make_unique<LightFish>(x, y);

    EXPECT_EQ(lightfish->getHitBox().getPosition().x, x);
    EXPECT_EQ(lightfish->getHitBox().getPosition().y, y);
    EXPECT_NE(lightfish->getHitBox().getTexture(), nullptr);
}

TEST(Baby, Constructor) {
    float x = 100.0f;
    float y = 150.0f;

    std::unique_ptr<Baby> baby = std::make_unique<Baby>(x, y);

    EXPECT_EQ(baby->getHitBox().getPosition().x, x);
    EXPECT_EQ(baby->getHitBox().getPosition().y, y);
    EXPECT_NE(baby->getHitBox().getTexture(), nullptr);
}


// Detection

TEST(Interactible, updateVisibility) {
    sf::Vector2f babyPosition(100.0f, 100.0f);

    std::unique_ptr<Baby> baby = std::make_unique<Baby>(babyPosition.x, babyPosition.y);
    //baby a un rayon de 50
    sf::CircleShape lightCircle(10.0f);
    // Le bout du cercle : 2 rayons 
    lightCircle.setPosition(100.0f + baby->getHitBox().getRadius() * 1.9, 100.0f);

    baby->updateVisibility(lightCircle);

    ASSERT_TRUE(baby->isVisible());

    lightCircle.setPosition(100.0f + baby->getHitBox().getRadius() * 2.1, 100.0f);

    baby->updateVisibility(lightCircle);

    ASSERT_FALSE(baby->isVisible());
}

