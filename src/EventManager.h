#pragma once
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class EventManager {
public:
	// Shark
	void endGame() { mEndGame = true; }
	bool isEndGame() const { return mEndGame; }

	// Baby
	void winLevel() { mWinLevel = true; }
	bool isWinLevel() const { return mWinLevel; }
	//LightFish
	void endGameEaten(sf::Vector2f pos) { mEndGameEaten = true; endPos = pos; }
	bool isEaten() { return mEndGameEaten; }
	sf::Vector2f getEndPos() { return endPos; }
	// Reset
	void reset() { mEndGame = false; mWinLevel = false; mEndGameEaten = false; endPos = sf::Vector2f(0, 0);}

private:
	bool mEndGame = false;
	bool mWinLevel = false;
	bool mEndGameEaten = false;

	sf::Vector2f endPos;

};

#endif // !EVENTMANAGER_H