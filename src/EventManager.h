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
	// Reset
	void reset() { mEndGame = false; mWinLevel = false; }
private:
	bool mEndGame = false;
	bool mWinLevel = false;
};

#endif // !EVENTMANAGER_H