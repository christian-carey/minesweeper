//
// Created by Christian Carey on 11/29/22.
//

#pragma once

int launch();
// Launches the program

void restart();
// Resets all states/objects and generates a default game state (random board) and turns off debug mode if active.

void render();
// Draws the all UI elements according to the current gameState and debug mode.

void toggleDebugMode();
// Flips the debug mode on/off. (Debug mode should initially be off/false.)

bool getDebugMode();
// Returns the true if debug mode is active, and false otherwise.

int gameLoop();
// Encapsulates event-polling, rendering, and other logic necessary to handle input and output for the game.

void rightClick(sf::Event event);
// Checks for tile pushes when mouse is right clicked

void leftClick(sf::Event event);
// Checks for button pushes when mouse is left clicked

void launchTest(int testBoard);
// Launches test board

void populateAdjacentMineCount();
// Populates each tile with adjacent mine count

void DrawFlagCount();
// Draws the flag count to the UI
