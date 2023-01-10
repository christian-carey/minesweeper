//
// Created by Christian Carey on 11/29/22.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"

class Toolbox {
/* A toolbox class is often used to contain variables that would otherwise be accessed throughout an application;
 * it is a mechanism to avoid truly global variables.
 */
public:
    sf::RenderWindow window; // SFML application window
    GameState* gameState; // Primary game state representation
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets / starts new game
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2

    sf::Texture* debugTexture;
    sf::Texture* newGameTexture;
    sf::Texture* test1Texture;
    sf::Texture* test2Texture;
    sf::Sprite* debugSprite;
    sf::Sprite* newGameSprite;
    sf::Sprite* test1Sprite;
    sf::Sprite* test2Sprite;

    sf::Texture* faceHappyTexture;
    sf::Texture* faceLoseTexture;
    sf::Texture* faceWinTexture;
    sf::Texture* tileHiddenTexture;
    sf::Texture* tileRevealedTexture;
    sf::Texture* mineTexture;
    sf::Texture* flagTexture;
    sf::Texture* digitsTexture;
    //sf::Sprite* newGameSprite;

    static Toolbox& getInstance();
    // Returns a reference to the singular Toolbox instance.

private:
    static Toolbox toolbox; // Singleton instance
    Toolbox(const Toolbox&); // Copy constructor
    Toolbox& operator=(const Toolbox&); // Copy assignment
    Toolbox();
    ~Toolbox();

};

