#include "Shark.h"
#include <iostream>
#include "Game.h"


Shark::Shark(float x, float y)
	: Interactible(static_cast<std::string>("resources/shark.png"), sf::CircleShape(50.f), 1.5f, x, y) {
	std::cout << "Shark spawn" << std::endl;
	setupFSM();
}

void Shark::setupFSM() {
	fsm.add_transitions({
		{ SharkStates::Patrol, SharkStates::Hunt, SharkTriggers::SeePlayer, [this] { return isVisible(); }, [] { std::cout << "Switching to Hunt mode\n"; } },
		{ SharkStates::Hunt, SharkStates::Patrol, SharkTriggers::LosePlayer, [this] { return !isVisible(); }, [] { std::cout << "Switching to Patrol mode\n"; } }
		});
}

void Shark::effect(EventManager* eventManager)
{
	std::cout << "Shark effect" << std::endl;
	eventManager->endGame();
}

void Shark::update(sf::Time deltaTime)
{
    fsm.execute(isVisible() ? SharkTriggers::SeePlayer : SharkTriggers::LosePlayer);

    switch (fsm.state()) {
    case SharkStates::Patrol:
		patrol(deltaTime);
        break;

    case SharkStates::Hunt:
		hunt(deltaTime);
        break;
    }
}

float Shark::trueHitBox() {
	return hitBoxBonus + hitBoxInteractible.getRadius();
}

void Shark::patrol(sf::Time deltaTime) {
	if (hitBoxInteractible.getPosition().x > SCREEN_WIDTH - 2 * hitBoxInteractible.getRadius() || hitBoxInteractible.getPosition().x < 0) {
		speed = -speed;
	}
	hitBoxInteractible.move(sf::Vector2f(1,0) * speed * deltaTime.asSeconds());
}

void Shark::hunt(sf::Time deltaTime) {
	hitBoxInteractible.move(normalize(lightPosition - hitBoxInteractible.getPosition() - sf::Vector2f(1.f,1.f)*hitBoxInteractible.getRadius()) * abs(speed) * deltaTime.asSeconds());
}