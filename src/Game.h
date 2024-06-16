#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <random>

#include "Interactible.h"
#include "Shark.h"
#include "EventManager.h"
#include "Baby.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

class Game
{
public :
	Game();
	void run();
	void endGame();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	void generateLevel();
	
	void resetTimer();
	bool isTimeUp() const;
	bool isInteractibleVisible(sf::CircleShape& hitbox) const;
	void gameOverScreen();
	void nextLevelScreen();

	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	sf::RenderWindow mWindow;
	sf::CircleShape mLightCircle;
	std::vector<std::unique_ptr<Interactible>> mInteractibles;
	sf::Clock mClock;
	sf::Time mTimeRemaining;

	sf::Texture textureBG;
	sf::Texture textureLL;
	sf::Sprite sprite;

	EventManager mEventManager;
	bool mGameOver = false;

	float littleLightRadius = 50;
	int offset = 100;
};

#endif // GAME_H
