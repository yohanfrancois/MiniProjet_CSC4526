#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Timer
{
public:
	Timer(float time);
	void update(sf::Time deltaTime);
	sf::Time getTimeRemaining() const;
	bool isTimeUp() const;
	void resetTimer();
	void draw(sf::RenderWindow& window) const;
	void setInitialTime(sf::Time time) { mInitialTime = time; }
	sf::Time getInitialTime() const { return mInitialTime; }
private:
	sf::Time mTimeRemaining;
	sf::Time mInitialTime;
};

#endif // !TIMER_H

