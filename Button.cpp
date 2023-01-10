//
// Created by Christian Carey on 11/29/22.
//

#include "Button.h"


/* This class will be used to implement each button widget.
 * Widgets are responsible for rending themselves, originating interaction (e.g., clicking), and conveying state to the user.
 */

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) : func(_onClick)
{   // Constructs a new object at the specified _position which invokes the _onClick callback when clicked.
    position = _position;
}

sf::Vector2f Button::getPosition()
{   // Returns the position of the button.
    return position;
}

sf::Sprite* Button::getSprite()
{   // Returns the current sprite of the button.
    return sprite;
}

void Button::setSprite(sf::Sprite* _sprite)
{   // Sets this button’s visualization to the specified _sprite.
    sprite = _sprite;
    sprite->setPosition(position);
}
