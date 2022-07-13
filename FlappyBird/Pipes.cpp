#include "Pipes.h"

Pipes::Pipes()
{
	//properly load textures and initial positions of pipes
	topPipeTexture.loadFromFile("Top_Pipe.png");
	botPipeTexture.loadFromFile("Bot_Pipe.png");
	
	topPipeSprite.setOrigin(50, 0);
	botPipeSprite.setOrigin(50, pipeHeight);

	topPipeSprite.setScale(-1, pipeScale);
	botPipeSprite.setScale(1, pipeScale);

	top_pipe_y = gap_height - (PIPE_SEPERATION / 2) - (pipeHeight * pipeScale);
	bot_pipe_y = gap_height + (PIPE_SEPERATION / 2) + (pipeHeight * pipeScale);
	topPipeSprite.setPosition(pipe_posX, top_pipe_y);
	botPipeSprite.setPosition(pipe_posX, bot_pipe_y);
}

//updates positions of pipes as they move towards player
void Pipes::update()
{
	if (isActive)
	{
		pipe_posX -= SCROLL_SPEED;
		topPipeSprite.setPosition(pipe_posX, top_pipe_y);
		botPipeSprite.setPosition(pipe_posX, bot_pipe_y);
		topPipeSprite.setTexture(topPipeTexture);
		botPipeSprite.setTexture(botPipeTexture);
	}
}

//spawns a "new" pair of pipes to move towards player
void Pipes::spawn(float prevHeight, int index)
{
	if (!isActive)
	{
		//tries to not have spaces on opposite sides of screen
		if (prevHeight < 300)
		{
			gap_height = rand() % (gap_range) + prevHeight;
		}
		else if (prevHeight > SCREEN_HEIGHT - 300)
		{
			gap_height = -(rand() % (gap_range)) + prevHeight;
		}
		else
		{
			gap_height = rand() % (gap_range * 2) + prevHeight - (0.5 * gap_range);
		}
		
		//ensures gaps are not too close to the top or bottom of the screen
		if (gap_height < 200)
		{
			gap_height = 200;
		}
		else if (gap_height > SCREEN_HEIGHT - 300)
		{
			gap_height = SCREEN_HEIGHT - 300;
		}
		
		//sets the pipe positions
		pipe_posX = SCREEN_WIDTH;
		top_pipe_y = gap_height - (PIPE_SEPERATION / 2) - (pipeHeight * pipeScale);
		bot_pipe_y = gap_height + (PIPE_SEPERATION / 2) + (pipeHeight * pipeScale);
		topPipeSprite.setPosition(pipe_posX, top_pipe_y);
		botPipeSprite.setPosition(pipe_posX, bot_pipe_y);
		isActive = true;
		isScored = false;
		pipe_index = index;
	}
}
