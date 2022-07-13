#include "Environment.h"

Ground::Ground()
{
	//initializes environment textures
	groundTexture.loadFromFile("Ground.png");
	groundSprite.setTexture(groundTexture);
	groundSprite.setScale(2, 1);
	groundSprite.setPosition(0, SCREEN_HEIGHT - GROUND_HEIGHT);

	cloudTexture.loadFromFile("Cloud.png");
	cloudSprite.setTexture(cloudTexture);
	cloudSprite.setScale(2, 1);
	cloudSprite.setPosition(0, GROUND_HEIGHT-100);
}