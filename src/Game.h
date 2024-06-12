#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Game
{
public :
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	void generateLevel();
	void resetTimer();
	bool isTimeUp() const;
	bool isInteractibleVisible(const sf::CircleShape& interactible) const;

private: 
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	sf::RenderWindow mWindow;
	sf::CircleShape mLightCircle;
	sf::CircleShape mInteractibleTest;
	sf::Clock mClock;
	sf::Time mTimeRemaining;

	sf::Texture texture;
	sf::Sprite sprite;


};

#endif // GAME_H
