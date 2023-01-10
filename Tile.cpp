//
// Created by Christian Carey on 11/29/22.
//

#include "Tile.h"
#include "Toolbox.h"
#include "minesweeper.h"
#include <array>


Tile::Tile(sf::Vector2f position)
{   // Constructs a new tile object at the designated _position.
    location = position;
    neighbors = new std::array<Tile*, 8>();
    state = HIDDEN;
    mineTile = false;
}

Tile::~Tile()
{
    if (neighbors != nullptr)
    {
        delete neighbors;
    }
}

sf::Vector2f Tile::getLocation()
{   // Returns the position of this tile.
    return location;
}

Tile::State Tile::getState()
{   // Returns current state of this tile.
    return state;
}

std::array<Tile*, 8>& Tile::getNeighbors()
{   // Returns pointer to array of Tile pointers (see Figure 2 for ordering).
    Toolbox &toolbox = Toolbox::getInstance();

    const int y[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int x[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for(int i=0; i<8; ++i)// check the spaces around it
    {
        if (inBounds(row + y[i], column + x[i]))
        {
            Tile* tile = (toolbox.gameState->board[column + x[i]][row + y[i]]);
            (*neighbors)[i] = tile;
        }
    }
    return *neighbors;
}

bool Tile::inBounds(int row, int col)
{
    Toolbox& toolbox = Toolbox::getInstance();
    int rows = toolbox.gameState->rows;
    int columns = toolbox.gameState->columns;

    if (row < 0 || row >= rows)
        return false;
    if (col < 0 || col >= columns)
        return false;
    return true;
}

void Tile::setState(Tile::State _state)
{   // Sets the state of this tile. Should trigger other behaviors related to the state change (including visualization).
    state = _state;
}

void Tile::setNeighbors(std::array<Tile*, 8> _neighbors)
{   // Populates / replaces the neighboring tile container.
    if (neighbors != nullptr)
    {
        delete neighbors;
    }
    neighbors = new std::array<Tile*, 8>(_neighbors);
}

void Tile::onClickLeft()
{
    Toolbox& toolbox = Toolbox::getInstance();

    if (mineTile)
    {
        state = EXPLODED;
        toolbox.gameState->setPlayStatus(GameState::LOSS);

        // Set face to lose face
        toolbox.newGameSprite->setTexture(*toolbox.faceLoseTexture);
        toolbox.newGameButton->setSprite(toolbox.newGameSprite);
    }

    // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries.
    if (state == HIDDEN || state == FLAGGED)
    {
        if (state == FLAGGED)
            toolbox.gameState->flagCount++;

        state = REVEALED;

        toolbox.gameState->revealedTileCount++;

        // Check for win condition:
        if (toolbox.gameState->revealedTileCount == (toolbox.gameState->tileCount - toolbox.gameState->getMineCount()))
        {
            toolbox.gameState->setPlayStatus(GameState::WIN);

            // Set face to win face
            toolbox.newGameSprite->setTexture(*toolbox.faceWinTexture);
            toolbox.newGameButton->setSprite(toolbox.newGameSprite);
        }
    }

    if (getNumOfAdjMines() == 0)
    {
        this->revealNeighbors();
    }
}

void Tile::onClickRight()
{
    Toolbox& toolbox = Toolbox::getInstance();

    // Toggles this tile’s state between FLAGGED and HIDDEN.
    if (getState() == HIDDEN)
    {
        setState(FLAGGED);
        toolbox.gameState->flagCount--;
    }
    else if (getState() == FLAGGED)
    {
        setState(HIDDEN);
        toolbox.gameState->flagCount--;
    }
}

void Tile::draw()
{   // Render this tile to the screen according to is state.
    Toolbox& toolbox = Toolbox::getInstance();

    sf::Sprite sprite;
    sprite.setPosition(getLocation());
    if (getState() == HIDDEN || getState() == FLAGGED)
        sprite.setTexture(*toolbox.tileHiddenTexture);
    else if (getState() == REVEALED || getState() == EXPLODED)
        sprite.setTexture(*toolbox.tileRevealedTexture);
    toolbox.window.draw(sprite);

    if (getState() == REVEALED && getNumOfAdjMines() > 0)
    {
        sf::Texture numTexture;
        numTexture.loadFromFile("data/images/number_" + std::to_string(getNumOfAdjMines()) + ".png");
        sf::Sprite numSprite;
        numSprite.setPosition(getLocation());
        numSprite.setTexture(numTexture);
        toolbox.window.draw(numSprite);
    }

    if (getState() == FLAGGED)
    {
        sf::Sprite flagSprite;
        flagSprite.setPosition(getLocation());
        flagSprite.setTexture(*toolbox.flagTexture);
        toolbox.window.draw(flagSprite);
    }

    if ((getDebugMode() || toolbox.gameState->getPlayStatus() == GameState::LOSS ||
         toolbox.gameState->getPlayStatus() == GameState::WIN) && mineTile)
    {
        sf::Sprite bombSprite;
        bombSprite.setPosition(getLocation());
        bombSprite.setTexture(*toolbox.mineTexture);
        toolbox.window.draw(bombSprite);
    }

}

void Tile::revealNeighbors()
{   // Based on State and mine content of the tile neighbors, set their state to REVEALED.
    for (Tile* tile : *neighbors)
    {
        if (tile != nullptr && tile->getNumOfAdjMines() == 0 && (tile->getState() == HIDDEN || tile->getState() == FLAGGED))
        {
            tile->onClickLeft();
            tile->revealNeighbors();
        }
        else if (tile != nullptr && (tile->getState() == HIDDEN || tile->getState() == FLAGGED))
        {
            tile->onClickLeft();
        }
    }
}

bool Tile::getMineTileBool()
{   // returns mine tile bool
    return mineTile;
}

int Tile::getNumOfAdjMines()
{   // Returns the number of adjacent mines
    return numOfAdjMines;
}

void Tile::setNumOfAdjMines(int numOfMines)
{   // Sets the number of adjacent mines
    numOfAdjMines = numOfMines;
}

void Tile::setRow(int _row)
{   // Sets the row number of tile
    row = _row;
}

void Tile::setColumn(int _column)
{   // Sets the column number of tile
    column = _column;
}
