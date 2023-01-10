//
// Created by Christian Carey on 11/29/22.
//

#include <fstream>
#include <random>
#include <array>
#include "GameState.h"
#include "Toolbox.h"


/* The GameState object should contain the Tile objects that represent the locations in the game and play status.
 */
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines)
{
    mineCount = _numberOfMines;
    flagCount = _numberOfMines;
    status = PLAYING;

    columns = _dimensions.x;
    rows = _dimensions.y;

    tileCount = columns * rows;
    revealedTileCount = 0;

    //Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines.
    int xLocation = 0;

    for (int i = 0; i < columns; i++)
    {
        board.emplace_back(std::vector<Tile *>());
        int yLocation = 0;
        for (int j = 0; j < rows; j++)
        {
            Tile* tile = new Tile(sf::Vector2f(xLocation, yLocation));
            tile->setRow(j);
            tile->setColumn(i);
            board[i].emplace_back(tile);
            yLocation += 32;
        }
        xLocation += 32;
    }

    // Generate random mines:
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> colDis(0, columns-1);
    std::uniform_int_distribution<> rowDis(0, rows-1);
    for (int i = 0; i < mineCount; i++)
    {
        bool minePlaced = false;
        while (!minePlaced)
        {
            int randomColumn = colDis(rng);
            int randomRow = rowDis(rng);
            if (!board[randomColumn][randomRow]->mineTile)
            {
                board[randomColumn][randomRow]->mineTile = true;
                minePlaced = true;
            }
        }
    }
}

GameState::GameState(const char* filepath)
{
    // Constructs a game state based on the size, mine placement, and mine number specified at filepath.
    Toolbox& toolbox = Toolbox::getInstance();

    status = PLAYING;

    // Read in bomb board from file
    std::string line;
    std::ifstream infile(filepath, std::ios::binary);
    while (std::getline(infile, line))
    {
        std::vector<bool> row;

        for (char &c : line) {
            if (c == 48 || c == 49)
                row.push_back(c - '0');
        }
        if (!row.empty())
            bombBoard.push_back(row);
    }

    rows = bombBoard.size();
    columns = bombBoard[0].size();

    // Set up main board
    int xLocation = 0;
    for (int i = 0; i < columns; i++)
    {
        board.emplace_back(std::vector<Tile *>());

        int yLocation = 0;
        for (int j = 0; j < rows; j++)
        {
            Tile* tile(new Tile(sf::Vector2f(xLocation, yLocation)));
            tile->setRow(j);
            tile->setColumn(i);
            board[i].push_back(tile);
            yLocation += 32;
        }
        xLocation += 32;
    }

    // Set up mines
    mineCount = 0;
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            board[i][j]->mineTile = bombBoard[j][i];

            if (board[i][j]->mineTile)
                mineCount++;
        }
    }
    tileCount = rows * columns;
    revealedTileCount = 0;
    flagCount = mineCount;
}

GameState::~GameState(){
    // Destructor
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            delete board[i][j];
        }
    }
}

int GameState::getFlagCount()
{   // Current count of the number of flags placed on the screen.
    return flagCount;
}

int GameState::getMineCount()
{   // Current count of the number of mines actually on the board.
    return mineCount;
}

Tile* GameState::getTile(int x, int y)
{   // Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds.
    if (x < 800 && x >= 0)
        if (y < 512 && y >= 0)
        {
            int column = x / 32;
            int row = y / 32;
            return board[column][row];
        }
    return nullptr;
}

GameState::PlayStatus GameState::getPlayStatus()
{   // Returns the play status of the game.
    return status;
}

void GameState::setPlayStatus(PlayStatus _status)
{   // Sets the play status of the game.
    status = _status;
}
