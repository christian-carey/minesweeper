//
// Created by Christian Carey on 11/29/22.
//

#include <iostream>
#include "Toolbox.h"
#include "minesweeper.h"


/* A toolbox class is often used to contain variables that would otherwise be accessed throughout an application;
 * it is a mechanism to avoid truly global variables.
 */

Toolbox& Toolbox::getInstance()
{   // Returns a reference to the singular Toolbox instance.
    static Toolbox toolbox;
    return toolbox;
}

Toolbox::Toolbox()
{   // Default constructor;
    // This method initializes the buttons, window, game board, and any other elements necessary to play the game.
    // Initialize button textures:
    debugTexture = new sf::Texture();
    newGameTexture = new sf::Texture();
    test1Texture = new sf::Texture();
    test2Texture = new sf::Texture();

    // Buttons:
    debugButton = new Button(sf::Vector2f(496,512), [](){ toggleDebugMode(); });
    debugTexture->loadFromFile("data/images/debug.png");
    debugSprite = new sf::Sprite(*debugTexture);
    debugButton->setSprite(debugSprite);

    newGameButton = new Button(sf::Vector2f(368,512), [](){ restart(); });
    newGameTexture->loadFromFile("data/images/face_happy.png");
    newGameSprite = new sf::Sprite(*newGameTexture);
    newGameButton->setSprite(newGameSprite);

    testButton1 = new Button(sf::Vector2f(560,512), [](){ launchTest(1); });
    test1Texture->loadFromFile("data/images/test_1.png");
    test1Sprite = new sf::Sprite(*test1Texture);
    testButton1->setSprite(test1Sprite);

    testButton2 = new Button(sf::Vector2f(624,512), [](){ launchTest(2);  });
    test2Texture->loadFromFile("data/images/test_2.png");
    test2Sprite = new sf::Sprite(*test2Texture);
    testButton2->setSprite(test2Sprite);

    // Window:
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Christian Carey");

    // Game Board:
    gameState = new GameState();

    // Textures:
    faceHappyTexture = new sf::Texture();
    faceHappyTexture->loadFromFile("data/images/face_happy.png");
    faceLoseTexture = new sf::Texture();
    faceLoseTexture->loadFromFile("data/images/face_lose.png");
    faceWinTexture = new sf::Texture();
    faceWinTexture->loadFromFile("data/images/face_win.png");
    tileHiddenTexture = new sf::Texture();
    tileHiddenTexture->loadFromFile("data/images/tile_hidden.png");
    tileRevealedTexture = new sf::Texture();
    tileRevealedTexture->loadFromFile("data/images/tile_revealed.png");
    mineTexture = new sf::Texture();
    mineTexture->loadFromFile("data/images/mine.png");
    flagTexture = new sf::Texture();
    flagTexture->loadFromFile("data/images/flag.png");
    digitsTexture = new sf::Texture();
    digitsTexture->loadFromFile("data/images/digits.png");
}

Toolbox::~Toolbox()
{
    delete debugTexture;
    delete newGameTexture;
    delete test1Texture;
    delete test2Texture;
    delete debugSprite;
    delete newGameSprite;
    delete test1Sprite;
    delete test2Sprite;

    delete debugButton;
    delete newGameButton;
    delete testButton1;
    delete testButton2;

    delete gameState;

    delete faceHappyTexture;
    delete faceLoseTexture;
    delete faceWinTexture;
    delete tileHiddenTexture;
    delete tileRevealedTexture;
    delete mineTexture;
    delete flagTexture;
    delete digitsTexture;
}



