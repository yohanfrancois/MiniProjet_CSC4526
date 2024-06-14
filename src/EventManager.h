#pragma once
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class EventManager {
public:
	// Shark
	void endGame() { mEndGame = true; }
	bool isEndGame() const { return mEndGame; }

	// Reset
	void reset() { mEndGame = false; }
private:
	bool mEndGame = false;
};

#endif // !EVENTMANAGER_H