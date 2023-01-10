//
// Created by Christian Carey on 11/29/22.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "minesweeper.h"

class Tile
{
/* This class implements the tile widgets that make up the board.
 * The class can be optionally subclassed to further encapsulate special traits.
 * Each tile’s neighbor configuration can vary (see Figure 1).
 * When a tile is adjacent to the edge of the board, the neighbor pointer should be a nullptr value. */
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED }; // Represents tile’s current UI state (visualization).

    Tile(sf::Vector2f position);
    // Constructs a new tile object at the designated _position.

    sf::Vector2f getLocation();
    // Returns the position of this tile.

    State getState();
    // Returns current state of this tile.

    std::array<Tile*, 8>& getNeighbors();
    // Returns pointer to array of Tile pointers.

    void setState(State _state);
    // Sets the state of this tile. Should trigger other behaviors related to the state change (including visualization).

    void setNeighbors(std::array<Tile*, 8> _neighbors);
    // Populates / replaces the neighboring tile container.

    void onClickLeft();
    // Defines the reveal behavior for a tile when the left mouse button is clicked inside its boundaries.

    void onClickRight();
    // Toggles this tile’s state between FLAGGED and HIDDEN.

    void draw();
    // Render this tile to the screen according to is state.

protected:

    void revealNeighbors();
    // Based on State and mine content of the tile neighbors, set their state to REVEALED.

private:
    ~Tile();

    bool inBounds( int row, int col );
    // Finds out if tile is a neighbor

    bool getMineTileBool();
    // returns mine tile bool

    int getNumOfAdjMines();
    // Returns the number of adjacent mines

    void setNumOfAdjMines(int numOfMines);
    // Sets the number of adjacent mines

    void setRow(int _row);
    // Sets the row number of tile

    void setColumn(int _column);
    // Sets the column number of tile

    bool mineTile;
    int numOfAdjMines;
    int row;
    int column;

    State state;
    sf::Vector2f location;
    std::array<Tile*, 8>* neighbors = nullptr;

    friend class GameState;
    friend void populateAdjacentMineCount();
};