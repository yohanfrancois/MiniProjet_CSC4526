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

	// Texture background
	if (!textureBG.loadFromFile("resources/background.png")) {
		cout << "can't find background";
	}

	// Texture Eaten
	if (!lightFishTexture.loadFromFile("resources/lightFish.png")) {
		cout << "can't find light fish";
	}

	
	

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
		render();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}

		
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
			if (event.key.code == sf::Keyboard::R && (mGameOver == true))
			{
				resetTimer();
				generateLevel();
			}
		}
	}
}

void Game::update(sf::Time deltaTime)
{

	
	
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	mLightCircle.setPosition(static_cast<sf::Vector2f>(mousePosition));

	if (mGameOver)
	{
		return;
	}

	for (auto& interactible : mInteractibles)
	{
		interactible->updateVisibility(mLightCircle);
		if (interactible->isVisible() && interactible->getVisibilityClock().getElapsedTime().asSeconds() >= interactible->getReactionTime())
		{
			interactible->effect(&mEventManager);
			interactible->resetVisibilityClock();
		}
		interactible->update(deltaTime);
	}

	mTimeRemaining -= deltaTime;
	if (isTimeUp())
	{
		mEventManager.endGame();
	}

	if (mEventManager.isEaten()) {
		endGameEaten();
	}


	if (mEventManager.isEndGame() || mEventManager.isWinLevel())
	{
		endGame();
	}



}

void Game::render()
{
	// Clear the window and draw background
	mWindow.clear();
	mWindow.draw(bgSprite);

	if (mEventManager.isEndGame())
	{
		gameOverScreen();
		return;
	}
	if (mEventManager.isWinLevel())
	{
		nextLevelScreen();
		return;
	}

	std::vector<sf::Vector2f> lightPositions;
	std::vector<float> lightRadiuss;

	lightPositions.push_back(sf::Vector2f(mLightCircle.getPosition().x, mWindow.getSize().y - mLightCircle.getPosition().y));
	lightRadiuss.push_back(mLightCircle.getRadius());

	// Interactibles 
	for (auto& interactible : mInteractibles)
	{
		// Draw
		interactible->draw(mWindow);

		//Shader Infos
		if (interactible->isLightSource()) {
			lightPositions.push_back(sf::Vector2f(interactible->getHitBox().getPosition().x  + interactible->getHitBox().getRadius(), mWindow.getSize().y - interactible->getHitBox().getPosition().y - interactible->getHitBox().getRadius()));
			lightRadiuss.push_back(interactible->getHitBox().getRadius());
		}
	}

	// SHADER
	sf::Shader shader;
	shader.loadFromFile("resources/shader.frag", sf::Shader::Fragment);

	// Set shader uniforms
	shader.setUniformArray("lightPositions", &lightPositions[0], lightPositions.size());
	shader.setUniformArray("lightRadiuss", &lightRadiuss[0], lightRadiuss.size());

	// BLENDMODE
	sf::BlendMode blendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha);

	sf::RenderStates states;
	states.shader = &shader;
	states.blendMode = blendMode;
	// Draw background with light circle
	mWindow.draw(bgSprite, states);
	

	mWindow.display();
}	

void Game::generateLevel()
{

	//Background
	textureBG.setSmooth(true);
	bgSprite.setTexture(textureBG);
	sf::Vector2u textureSize = textureBG.getSize();
	bgSprite.setScale(SCREEN_WIDTH / static_cast<float>(textureSize.x), SCREEN_HEIGHT / static_cast<float>(textureSize.y));

	mEventManager.reset();
	mGameOver = false;
	mInteractibles.clear();

	// Baby
	int rangeSizex = SCREEN_WIDTH - 1 - offset;
	int rangeSizey = SCREEN_HEIGHT - 1 - offset;
	float x = static_cast<float>((std::rand() % rangeSizex)+offset);
	float y = static_cast<float>((std::rand() % rangeSizey)+offset);
	mInteractibles.push_back(std::make_unique<Baby>(x, y));

	// Générer une séquence random d'intéractibles parmi ceux existants et les faire spawn sans overlap entre eux (c'est dur mais un truc approximatif suffirait. Autre problème est 
	// qu'ils sortent de l'écran parfois mais juste un offset)

	for (int i = 0; i < 2; ++i) {
		x = static_cast<float>((std::rand() % rangeSizex) + offset);
		y = static_cast<float>((std::rand() % rangeSizey) + offset);
		mInteractibles.push_back(std::make_unique<Shark>(x, y));
	}
	x = static_cast<float>((std::rand() % rangeSizex) + offset);
	y = static_cast<float>((std::rand() % rangeSizey) + offset);
	mInteractibles.push_back(std::make_unique<LightFish>(x, y));
	
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

void Game::nextLevelScreen() {

	sf::Font font;
	font.loadFromFile("resources/font.ttf");
	sf::Text winLevelText("Good Job but ... ", font, 100);
	sf::Text winLevelText2("there are plenty left ", font, 100);
	winLevelText.setFillColor(sf::Color::Red);
	winLevelText.setPosition(SCREEN_WIDTH / 2.f - winLevelText.getLocalBounds().width / 2.f, SCREEN_HEIGHT / 2.f - winLevelText.getLocalBounds().height / 2.f);
	winLevelText2.setFillColor(sf::Color::Red);
	winLevelText2.setPosition(SCREEN_WIDTH / 2.f - winLevelText2.getLocalBounds().width / 2.f, SCREEN_HEIGHT / 2.f + 100.f);
	//Ecrire des statistiques intéressantes (timer, nombre de fish vu, nombre de fish pas vu que sais je)
	mWindow.draw(winLevelText);
	mWindow.draw(winLevelText2);
	mWindow.display();
}

void Game::endGameEaten() {

	mInteractibles.clear();

	bgSprite.setTexture(lightFishTexture);
	sf::Vector2u textureSize = textureBG.getSize();
	bgSprite.setScale(SCREEN_WIDTH / static_cast<float>(textureSize.x), SCREEN_HEIGHT / static_cast<float>(textureSize.y));
	endGame();
}