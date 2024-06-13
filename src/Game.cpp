#include "Game.h"
#include <iostream>

using namespace std;

Game::Game()
	: mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Babyssal")
	, mLightCircle()
	, mTimeRemaining(sf::seconds(30.f))
{	
	srand(static_cast<unsigned int>(std::time(nullptr)));
	
	mLightCircle.setRadius(150.f);
	mLightCircle.setOrigin(mLightCircle.getRadius(), mLightCircle.getRadius());

	// Sprite background
	if (!texture.loadFromFile("resources/background.png")) {
		cout << "can't find background";
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sf::Vector2u textureSize = texture.getSize();
	sprite.setScale(SCREEN_WIDTH / static_cast<float>(textureSize.x), SCREEN_HEIGHT / static_cast<float>(textureSize.y));

	generateLevel();
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

	for (auto& interactible : mInteractibles)
	{
		interactible->updateVisibility(mLightCircle);
		if (interactible->isVisible() && interactible->getVisibilityClock().getElapsedTime().asSeconds() >= interactible->getReactionTime())
		{
			interactible->effect();
			interactible->resetVisibilityClock();
		}
	}

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
	for (auto& interactible : mInteractibles)
	{
		interactible->draw(mWindow);
	}

	// SHADER
	sf::Shader shader;
	shader.loadFromFile("resources/shader.frag", sf::Shader::Fragment);
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
	mInteractibles.clear();
	float x = static_cast<float>(std::rand() % SCREEN_WIDTH);
	float y = static_cast<float>(std::rand() % SCREEN_HEIGHT);
	mInteractibles.push_back(std::make_unique<Shark>(x, y));
	cout << "Shark created at " << x << " " << y << endl;
}

void Game::resetTimer()
{
	mTimeRemaining = sf::seconds(30.f);
}

bool Game::isTimeUp() const
{
	return mTimeRemaining <= sf::Time::Zero;
}

bool Game::isInteractibleVisible(sf::CircleShape& hitbox) const
{
	sf::Vector2f hitboxPosition = hitbox.getPosition();
	sf::Vector2f lightPosition = mLightCircle.getPosition();
	float distance = sqrt(pow(hitboxPosition.x - lightPosition.x, 2) + pow(hitboxPosition.y - lightPosition.y, 2));
	return distance <= mLightCircle.getRadius();
}

