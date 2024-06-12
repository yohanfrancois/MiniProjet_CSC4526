#include "Game.h"
#include <iostream>

Game::Game()
	: mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Babyssal")
	, mLightCircle()
	, mInteractibleTest()
	, mTimeRemaining(sf::seconds(30.f))
{
	mLightCircle.setRadius(50.f);
	mLightCircle.setFillColor(sf::Color(255, 255, 0, 100));
	mLightCircle.setOrigin(mLightCircle.getRadius(), mLightCircle.getRadius());

	mInteractibleTest.setRadius(30.f);
	mInteractibleTest.setFillColor(sf::Color::Green);
	mInteractibleTest.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	mLightCircle.setPosition(static_cast<sf::Vector2f>(mousePosition));
	mTimeRemaining -= deltaTime;
	if (isTimeUp())
	{
		std::cout << "Time's up!" << std::endl;
		resetTimer();
		generateLevel();
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mLightCircle);

	if (isInteractibleVisible(mInteractibleTest)) {
		mWindow.draw(mInteractibleTest);
	}

	mWindow.display();
}	

void Game::generateLevel()
{
	// Later
}

void Game::resetTimer()
{
	mTimeRemaining = sf::seconds(30.f);
}

bool Game::isTimeUp() const
{
	return mTimeRemaining <= sf::Time::Zero;
}

bool Game::isInteractibleVisible(const sf::CircleShape& interactible) const
{
	return mLightCircle.getGlobalBounds().intersects(interactible.getGlobalBounds());
}