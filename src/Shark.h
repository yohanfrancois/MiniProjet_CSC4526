#pragma once
#ifndef SHARK_H
#define SHARK_H

#include "Interactible.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "fsm.h" 
#include "Utils.h"

class Shark : public Interactible
{
public:
    Shark(float x, float y);
    void effect(EventManager* eventManager) override;
    void update(sf::Time deltaTime) override;
    float trueHitBox() override;
    float speed = 25.f; //public seulement pour simplifier la vie des tests Todo getter si modif ailleurs!

private:
    float hitBoxBonus = 90.f;
    
    enum class SharkStates { Patrol, Hunt };
    enum class SharkTriggers { SeePlayer, LosePlayer };

    FSM::Fsm<SharkStates, SharkStates::Patrol, SharkTriggers> fsm;
    
    void setupFSM();

    void hunt(sf::Time deltaTime);
    void patrol(sf::Time deltaTime);
};

#endif // !SHARK_H