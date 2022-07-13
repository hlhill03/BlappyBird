#pragma once
#include <SFML/Graphics.hpp>
#include "Source.h"
#include <Windows.h>
#include "Constants.h"
#include "Pipes.h"

class Player
{
public:
	sf::Sprite playerSprite;
	sf::Texture flying;
	sf::Texture falling;

	float spriteHeight;
	bool isAlive = true;
	bool isOnGround = false;
	float pos_x = 70;
	float pos_y = SCREEN_HEIGHT / 2;
	float vel_x = SCROLL_SPEED;
	float vel_y = 0;
	float GRAVITY = 0.5;
	int score = 0;

	Player();
	void update();
	void flap();
	void checkCollision(Pipes pipe);
	void resetPlayer();
};

