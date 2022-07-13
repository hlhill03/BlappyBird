#include "Player.h"

Player::Player()
{
	//loads player textures and sprite
	flying.loadFromFile("Bird_Flying.png");
	falling.loadFromFile("Bird_Falling.png");
	playerSprite.setPosition(pos_x,pos_y);
	playerSprite.setTexture(falling);
	playerSprite.setScale(1.5,1.5);
	spriteHeight = playerSprite.getLocalBounds().height;
}

//update position of player 
void Player::update()
{	
	//updates animation and movement of player
	if (!isOnGround)
	{
		vel_y += GRAVITY;
		if (vel_y < 0)
		{
			playerSprite.setTexture(flying);
		}
		else
		{
			playerSprite.setTexture(falling);
		}
		pos_y += vel_y;
	}

	//stops player from moving above screen
	if (pos_y <= 0)
	{
		pos_y = 0;
		vel_y = 0;
	}
	//checks if player is touching the ground
	else if (pos_y >= SCREEN_HEIGHT - GROUND_HEIGHT)
	{
		isAlive = false;
		isOnGround = true;
		pos_y = SCREEN_HEIGHT - GROUND_HEIGHT - (spriteHeight+ 15);
	}
	playerSprite.setPosition(pos_x, pos_y);
}

//upward movement of player
void Player::flap()
{
	if (isAlive)
	{
		vel_y = -10;
	}
}

//checks the collision of player with a pipe object
void Player::checkCollision(Pipes pipe)
{
	float pipe_x = pipe.pipe_posX - 100;
	//checks if player is within the width of a pipe
	if (pos_x >= pipe_x - 20 && pos_x <= pipe_x +100)
	{
		//checks if the player is vertically hitting a pipe
		if (pos_y >= pipe.gap_height + PIPE_SEPERATION / 2 || pos_y <= pipe.gap_height - PIPE_SEPERATION / 2)
		{
			isAlive = false;
			vel_x = 0;
		}
	}
}

//resets player to starting position and values
void Player::resetPlayer()
{
	isAlive = true;
	isOnGround = false;
	pos_x = 70;
	pos_y = SCREEN_HEIGHT / 2;
	vel_x = SCROLL_SPEED;
	vel_y = 0;
	score = 0;
}
