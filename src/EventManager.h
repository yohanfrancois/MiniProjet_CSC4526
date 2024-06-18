#pragma once
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class EventManager {
public:
	// Shark : lose
	void endGame() { mEndGame = true; }
	bool isEndGame() const { return mEndGame; }
	// Baby : win
	void winLevel() { mWinLevel = true; }
	bool isWinLevel() const { return mWinLevel; }
	//LightFish : scary lose
	void endGameEaten(sf::Vector2f pos) { mEndGameEaten = true; endPos = pos; }
	bool isEaten() const { return mEndGameEaten; }
	sf::Vector2f getEndPos() const { return endPos; }



	// Reset
	void reset() { mEndGame = false; mWinLevel = false; mEndGameEaten = false; endPos = sf::Vector2f(0, 0); timeToAdd = 0; }

	//air Bubbles : manipulate time remaining
	void addTime(float time) { timeToAdd = time; };
	float getTimeToAdd() const { return timeToAdd; };

private:
	bool mEndGame = false;
	bool mWinLevel = false;
	bool mEndGameEaten = false;

	sf::Vector2f endPos;
	float timeToAdd;
};

#endif // !EVENTMANAGER_H