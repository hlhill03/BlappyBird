#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>


class Pipes
{
public:
	sf::Sprite topPipeSprite;
	sf::Sprite botPipeSprite;
	sf::Texture topPipeTexture;
	sf::Texture botPipeTexture;

	int pipe_index;
	float pipe_posX = SCREEN_WIDTH;
	float gap_height = SCREEN_HEIGHT/2;
	float top_pipe_y;
	float bot_pipe_y;
	const float pipeHeight = 700;
	const float pipeScale = 1.5;
	int gap_range = 600;

	bool isActive = false;
	bool isScored = false;
	bool leftPipe = false;

	Pipes();
	void update();
	void spawn(float prevHeight, int index);
};

