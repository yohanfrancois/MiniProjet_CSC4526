#include "Timer.h"
#include "Game.h"

Timer::Timer(float time)
{
	mInitialTime = sf::seconds(time);
	mTimeRemaining = mInitialTime;
}

void Timer::update(sf::Time deltaTime)
{
	mTimeRemaining -= deltaTime;
}

sf::Time Timer::getTimeRemaining() const
{
	return mTimeRemaining;
}

bool Timer::isTimeUp() const
{
	return mTimeRemaining <= sf::Time::Zero;
}

void Timer::resetTimer()
{
	mTimeRemaining = mInitialTime;
}

void Timer::draw(sf::RenderWindow& window) const
{
	sf::RectangleShape timerBar;
	timerBar.setSize(sf::Vector2f(SCREEN_WIDTH * mTimeRemaining / mInitialTime, 20));
	timeBar.setPosition(0, 0);
	if (mTimeRemaining <= sf::seconds(5))
	{
		timerBar.setFillColor(sf::Color::Red);
	}
	else if (mTimeRemaining <= sf::seconds(10))
	{
		timerBar.setFillColor(sf::Color::Yellow);
	}
	else
	{
		timerBar.setFillColor(sf::Color::Green);
	}
	window.draw(timerBar);
}
