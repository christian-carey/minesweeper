//
// Created by Christian Carey on 11/29/22.
//

#pragma once

#include <SFML/Graphics.hpp>

class Button
{
/* This class will be used to implement each button widget.
 * Widgets are responsible for rending themselves, originating interaction (e.g., clicking), and conveying state to the user.
 */

std::function<void(void)> func;
sf::Vector2f position;
sf::Sprite* sprite = nullptr;

public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    // Constructs a new object at the specified _position which invokes the _onClick callback when clicked.

    sf::Vector2f getPosition();
    // Returns the position of the button.

    sf::Sprite* getSprite();
    // Returns the current sprite of the button.

    void setSprite(sf::Sprite* _sprite);
    // Sets this button’s visualization to the specified _sprite.

    void onClick() { func(); }
    // Invokes the button’s callback method (usually called when clicked).
};