#include "Source.h"
#include <iostream>

//defines game window and objects in window
sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Window");
Player player;
Ground ground;
std::vector<Pipes> pipes(3, Pipes());
sf::Font font;
sf::Text text;

int pipe_index = 1;
bool isReset;

//sets the nearest pipe to player to pass to collision check
void setNearestPipe(int index)
{
    for (auto it = pipes.begin(); it != pipes.end(); it++)
    {
        if (index > 3)
        {
            index = 1;
        }
        if (it->pipe_index == index)
        {
            it->leftPipe = true;
        }
    }
}

//resets vector of pipes
void resetPipes()
{
    for (auto it = pipes.begin(); it != pipes.end(); it++)
    {
        it->pipe_posX = SCREEN_WIDTH+500;
        it->gap_height = SCREEN_HEIGHT / 2;
        it->isActive = false;
        it->isScored = false;
        it->leftPipe = false;
        it->pipe_index = 0;
        it->top_pipe_y = it->gap_height - (PIPE_SEPERATION / 2) - (it->pipeHeight * it->pipeScale);
        it->bot_pipe_y = it->gap_height + (PIPE_SEPERATION / 2) + (it->pipeHeight * it->pipeScale);
        it->topPipeSprite.setPosition(it->pipe_posX, it->top_pipe_y);
        it->botPipeSprite.setPosition(it->pipe_posX, it->bot_pipe_y);
    }
}

//resets state of game
void reset()
{
    pipe_index = 1;
    
    resetPipes();
    player.resetPlayer();

    pipes[1].spawn(SCREEN_HEIGHT / 2, pipe_index);
    pipe_index++;
    setNearestPipe(pipe_index);

}

//checks for space key being pressed
void getKeyPress()
{
    if (GetKeyState(VK_SPACE) & 0x8000)
    {
        player.flap();
    }
    //R key
    if (GetKeyState(0x52) & 0x8000)
    {
        reset();           
    }
}

int main()
{
    srand(time(NULL));
    reset();

    //Loads fonts
    if (!font.loadFromFile("Amatic-Bold.ttf"))
    {
        std::cout << "Font failed to load"<<std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setPosition(sf::Vector2f(SCREEN_WIDTH/2, 50));

    //game engine
    while (window.isOpen())
    {
        //initializes window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        } 

        window.clear(sf::Color(0, 255, 255));
        
        //check for player input
        getKeyPress();
        //update player
        player.update();
        
        //variables to check vector of pipes
        int pipeCount = 0;
        float pipe_x = SCREEN_WIDTH;
        float prevHeight = SCREEN_WIDTH;

        //iterates through each pair of pipes
        for (auto it = pipes.begin(); it != pipes.end(); it++)
        {
            //checks if pipes are active (on screen)
            if (it->isActive)
            {
                //checks the number of pipes on screen if there are less than 2 spawns another set
                pipe_x = it->pipe_posX;
                pipeCount++;

                //checks if player has collided with pipe
                player.checkCollision((*it));

                //if the player is alive
                if (player.isAlive)
                {
                    //update the pipe
                    it->update();
                    
                    //check if player has made it safely through pipes and score a point
                    if (player.pos_x >= it->pipe_posX && it->isScored == false)
                    {
                        player.score++;
                        it->isScored = true;
                    }
                    //check if pipe pair has reached left side of screen
                    if (pipe_x < 0)
                    {
                        //despawns pipe pair and spawns in a new set
                        it->isActive = false;
                        it->spawn(prevHeight, pipe_index);
                        it->leftPipe = false;
                        pipe_index++;
                        setNearestPipe(pipe_index);
                    }
                    //grabs the height of the previous pipe pair to ensure player can navigate through pipes
                    //attempt to make the game not have impossible pipes
                    if (it->leftPipe)
                    {
                        prevHeight = it->gap_height;
                    }
                }
                //update pipe sprites
                window.draw(it->topPipeSprite);
                window.draw(it->botPipeSprite);
            }
            //if a pipe has made it half way across the scree spawn another pipe
            else if (pipe_x < SCREEN_WIDTH / 2 && pipeCount < 3)
            {
                 it->spawn(prevHeight,pipe_index);
                 pipe_index++;                 
            }        
        }        
        //draw the enviornment and player
        window.draw(ground.groundSprite);
        //window.draw(ground.cloudSprite);
        window.draw(player.playerSprite);
        //update score
        text.setString(std::to_string(player.score));
        window.draw(text);       
        
        window.display();
        window.setFramerateLimit(60);
    }
}

