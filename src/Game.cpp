#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
	: mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Babyssal")
	, mLightCircle()
	, mInteractibleTest()
	, mTimeRemaining(sf::seconds(30.f))
{	
	mLightCircle.setRadius(100.f);
	mLightCircle.setFillColor(sf::Color::Yellow);
	mLightCircle.setOrigin(mLightCircle.getRadius(), mLightCircle.getRadius());

	mInteractibleTest.setRadius(30.f);
	mInteractibleTest.setFillColor(sf::Color::Green);
	mInteractibleTest.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);


	// Sprite background
	if (!texture.loadFromFile("textures/background.png")) {
		cout << "can't find background";
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(SCREEN_WIDTH / static_cast<float>(textureSize.x), SCREEN_HEIGHT / static_cast<float>(textureSize.y));

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
	// Clear the window and draw background
	mWindow.clear();
	mWindow.draw(sprite);

	// Interactibles 
	mWindow.draw(mInteractibleTest);

	// SHADER
	sf::Shader shader;
	shader.loadFromFile("textures/shader.frag", sf::Shader::Fragment);
	sf::Vector2f lightPosition(mLightCircle.getPosition().x, mWindow.getSize().y - mLightCircle.getPosition().y);
	shader.setUniform("lightPosition", lightPosition);
	shader.setUniform("lightRadius", mLightCircle.getRadius());

	// BLENDMODE
	sf::BlendMode blendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha);
	sf::RenderStates states;
	states.shader = &shader;
	states.blendMode = blendMode;

	// Draw background with light circle
	mWindow.draw(sprite, states);
	

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