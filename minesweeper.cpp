//
// Created by Christian Carey on 11/29/22.
//

#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include "Toolbox.h"
#include "minesweeper.h"


int launch()
{
    // This method is invoked directly by main() and is responsible for the game’s launch.
    Toolbox& toolbox = Toolbox::getInstance();

    restart();
    return gameLoop();
}

void restart()
{   // Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.
    // The new state should be a default game state (25x16 with 50 randomly placed mines).
    Toolbox &toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    toolbox.gameState = new GameState();

    // Set face to happy face
    toolbox.newGameSprite->setTexture(*toolbox.faceHappyTexture);
    toolbox.newGameButton->setSprite(toolbox.newGameSprite);

    populateAdjacentMineCount();
}

void render()
{   // Draws the all UI elements according to the current gameState and debug mode.
    Toolbox& toolbox = Toolbox::getInstance();

    toolbox.window.draw( *(toolbox.debugButton->getSprite()));
    toolbox.window.draw( *(toolbox.newGameButton->getSprite()));
    toolbox.window.draw( *(toolbox.testButton1->getSprite()));
    toolbox.window.draw( *(toolbox.testButton2->getSprite()));

    // Draw tiles:
    for (const std::vector<Tile *>& column : (toolbox.gameState->board))
    {
        for (auto const& tile : column)
            tile->draw();
    }

    // Draw flag count:
    DrawFlagCount();
}

void toggleDebugMode()
{   // Flips the debug mode on/off. (Debug mode should initially be off/false.)
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.gameState->debugMode = !toolbox.gameState->debugMode;
}

bool getDebugMode()
{   // Returns the true if debug mode is active, and false otherwise.
    Toolbox& toolbox = Toolbox::getInstance();
    return toolbox.gameState->debugMode;
}

int gameLoop()
{   // Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game.
    Toolbox& toolbox = Toolbox::getInstance();

    while (toolbox.window.isOpen())
    {
        toolbox.window.clear();
        render();
        toolbox.window.display();

        sf::Event event;
        while (toolbox.window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    toolbox.window.close();
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        rightClick(event);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        leftClick(event);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

void rightClick(sf::Event event)
{
    Toolbox& toolbox = Toolbox::getInstance();
    sf::FloatRect gameBounds = sf::FloatRect(0, 0, 800, 512);

    sf::Vector2f mouse = toolbox.window.mapPixelToCoords(sf::Mouse::getPosition(toolbox.window));

    if (gameBounds.contains(mouse))
    {
        // Return if state is win or loss
        if (toolbox.gameState->getPlayStatus() == GameState::WIN || toolbox.gameState->getPlayStatus() == GameState::LOSS)
            return;

        Tile* tile = toolbox.gameState->getTile(event.mouseButton.x, event.mouseButton.y);
        tile->onClickRight();
    }
}

void leftClick(sf::Event event)
{
    Toolbox& toolbox = Toolbox::getInstance();
    sf::FloatRect debugBounds = toolbox.debugButton->getSprite()->getGlobalBounds();
    sf::FloatRect newGameBounds = toolbox.newGameButton->getSprite()->getGlobalBounds();
    sf::FloatRect test1Bounds = toolbox.testButton1->getSprite()->getGlobalBounds();
    sf::FloatRect test2Bounds = toolbox.testButton2->getSprite()->getGlobalBounds();
    sf::FloatRect gameBounds = sf::FloatRect(0, 0, 800, 512);

    sf::Vector2f mouse = toolbox.window.mapPixelToCoords(sf::Mouse::getPosition(toolbox.window));

    if (debugBounds.contains(mouse))
        toolbox.debugButton->onClick();
    else if (newGameBounds.contains(mouse))
        toolbox.newGameButton->onClick();
    else if (test1Bounds.contains(mouse))
        toolbox.testButton1->onClick();
    else if (test2Bounds.contains(mouse))
        toolbox.testButton2->onClick();
    else if (gameBounds.contains(mouse))
    {
        // Return if state is win or loss
        if (toolbox.gameState->getPlayStatus() == GameState::WIN || toolbox.gameState->getPlayStatus() == GameState::LOSS)
            return;

        Tile* tile = toolbox.gameState->getTile(event.mouseButton.x, event.mouseButton.y);
        tile->onClickLeft();
    }
}

void launchTest(int testBoard)
{   // Launches test1 board
    Toolbox& toolbox = Toolbox::getInstance();

    std::string fileName = "data/boards/testboard" + std::to_string(testBoard) + ".brd";
    delete toolbox.gameState;
    toolbox.gameState = new GameState((fileName).c_str());

    // Set face to happy face
    toolbox.newGameSprite->setTexture(*toolbox.faceHappyTexture);
    toolbox.newGameButton->setSprite(toolbox.newGameSprite);

    populateAdjacentMineCount();
}

void populateAdjacentMineCount()
{   // Populates each tile with adjacent mine count

    Toolbox& toolbox = Toolbox::getInstance();

    // Count neighboring mines
    for (int i = 0; i < toolbox.gameState->columns; i++)
    {
        for (int j = 0; j < toolbox.gameState->rows; j++)
        {
            if (toolbox.gameState->board[i][j]->getMineTileBool())
                continue;

            int mineCount = 0;

            std::array<Tile *, 8>& neighbors = toolbox.gameState->board[i][j]->getNeighbors();
            for (Tile* tile : neighbors)
            {
                if (tile != nullptr && tile->getMineTileBool())
                {
                    mineCount++;
                }
            }
            // Set mineCount
            toolbox.gameState->board[i][j]->setNumOfAdjMines(mineCount);
        }
    }
}

void DrawFlagCount()
{   // Draws the flag count to the UI
    Toolbox& toolbox = Toolbox::getInstance();

    int flagCount = toolbox.gameState->getFlagCount();

    int hundredsIndex, tensIndex, onesIndex;

    hundredsIndex = flagCount / 100;
    tensIndex = abs(flagCount % 100) / 10;
    onesIndex = abs(flagCount % 10);

    // Hundreds Digit (and minus sign)
    sf::Sprite hundredsSprite;
    hundredsSprite.setPosition(0, 512);
    hundredsSprite.setTexture(*toolbox.digitsTexture);
    hundredsSprite.setTextureRect(sf::IntRect(hundredsIndex * 21, 0, 21, 32));
    // Check for negative number
    if (flagCount < 0)
    {
        hundredsSprite.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
    }
    toolbox.window.draw(hundredsSprite);

    // Tens Digit (and minus sign)
    sf::Sprite tensSprite;
    tensSprite.setPosition(21, 512);
    tensSprite.setTexture(*toolbox.digitsTexture);
    tensSprite.setTextureRect(sf::IntRect(tensIndex * 21, 0, 21, 32));
    toolbox.window.draw(tensSprite);

    // Ones Digit (and minus sign)
    sf::Sprite onesSprite;
    onesSprite.setPosition(42, 512);
    onesSprite.setTexture(*toolbox.digitsTexture);
    onesSprite.setTextureRect(sf::IntRect(onesIndex * 21, 0, 21, 32));
    toolbox.window.draw(onesSprite);
}

int main() { return launch(); }
