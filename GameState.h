//
// Created by Christian Carey on 11/29/22.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tile.h"

class GameState
{
/* The GameState object should contain the Tile objects that represent the locations in the game and play status. */
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    // Tracks the play status of the game, which is reflected in the behavior of the user interface and visualizations.

    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    // Constructs a new random game state with specified tile _dimensions and the specified _numberOfMines.

    GameState(const char* filepath);
    // Constructs a game state based on the size, mine placement, and mine number specified at filepath.

    int getFlagCount();
    // Current count of the number of flags placed on the screen.

    int getMineCount();
    // Current count of the number of mines actually on the board.

    Tile* getTile(int x, int y);
    // Returns a pointer to the Tile at the specified coordinates, or nullptr if out of bounds.

    PlayStatus getPlayStatus();
    // Returns the play status of the game.

    void setPlayStatus(PlayStatus _status);
    // Sets the play status of the game.

    ~GameState();

private:
    std::vector<std::vector< Tile * >> board;
    std::vector<std::vector<bool>> bombBoard;
    int rows;
    int columns;
    bool debugMode = false;
    int flagCount;
    int revealedTileCount;
    int tileCount;

    PlayStatus status;
    int mineCount;

    friend void populateAdjacentMineCount();
    friend void render();
    friend void toggleDebugMode();
    friend bool getDebugMode();
    friend class Tile;
};