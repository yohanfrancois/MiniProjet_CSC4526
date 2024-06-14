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
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::R && mGameOver == true)
			{
				resetTimer();
				generateLevel();
			}
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	if (mGameOver)
	{
		return;
	}
	
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	mLightCircle.setPosition(static_cast<sf::Vector2f>(mousePosition));

	for (auto& interactible : mInteractibles)
	{
		interactible->updateVisibility(mLightCircle);
		if (interactible->isVisible() && interactible->getVisibilityClock().getElapsedTime().asSeconds() >= interactible->getReactionTime())
		{
			interactible->effect(&mEventManager);
			interactible->resetVisibilityClock();
		}
	}

	mTimeRemaining -= deltaTime;
	if (isTimeUp())
	{
		mEventManager.endGame();
	}

	if (mEventManager.isEndGame())
	{
		endGame();
	}

}

void Game::render()
{
	// Clear the window and draw background
	mWindow.clear();
	mWindow.draw(sprite);

	if (mGameOver)
	{
		gameOverScreen();
		return;
	}

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
	mEventManager.reset();
	mGameOver = false;
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

void Game::endGame() 
{
	mGameOver = true;
}

void Game::gameOverScreen()
{
	sf::Font font;
	font.loadFromFile("resources/font.ttf");
	sf::Text gameOverText("Game Over", font, 100);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setPosition(SCREEN_WIDTH / 2.f - gameOverText.getLocalBounds().width / 2.f, SCREEN_HEIGHT / 2.f - gameOverText.getLocalBounds().height / 2.f);
	sf::Text restartText("Press R to restart", font, 50);
	restartText.setFillColor(sf::Color::White);
	restartText.setPosition(SCREEN_WIDTH / 2.f - restartText.getLocalBounds().width / 2.f, SCREEN_HEIGHT / 2.f + 100.f);
	mWindow.draw(restartText);
	mWindow.draw(gameOverText);
	mWindow.display();
}