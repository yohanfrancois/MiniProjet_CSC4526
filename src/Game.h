#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <random>

#include "Interactible.h"
#include "Shark.h"
#include "EventManager.h"
#include "Baby.h"
#include "LightFish.h"
#include "Timer.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define SECONDS_PER_LEVEL 30
#define DECREASE_RATIO 1.1f

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
	void generateBaby();
	void generateShark();
	void generateLightFish();
	
	bool isInteractibleVisible(sf::CircleShape& hitbox) const;
	void gameOverScreen();
	void nextLevelScreen();
	void endGameEaten();
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	sf::RenderWindow mWindow;
	
	std::vector<std::unique_ptr<Interactible>> mInteractibles;
	sf::Clock mClock;
	sf::Time mTimeRemaining;

	sf::Texture textureBG;
	sf::Texture lightFishTexture;
	sf::Texture textureLL;

	sf::Sprite bgSprite;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	EventManager mEventManager;
	bool mGameOver = false;

	float littleLightRadius = 50;
	int offset = 100;
	int mLevel = 1;

	int nbOfSharks = 2;
	int nbOfLightFish = 1;

	Timer mTimer;

	sf::CircleShape mLightCircle;
};

#endif // GAME_H
