#include <SFML/Graphics.hpp>
#pragma once
class CenteredText : public sf::Drawable
{

public:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Text txt;
    CenteredText(sf::Vector2f _position, sf::Vector2f _size, sf::String& _text, sf::Font& _font, unsigned int _font_size)
    {
        txt.setFont(_font);
        txt.setCharacterSize(_font_size);
        txt.setString(_text);
        txt.setPosition(_position);
        position = _position;
        size = _size;
        float xPos = (position.x + size.x / 2) - (txt.getLocalBounds().width / 2);
        float yPos = (position.y + size.y / 2.2) - (txt.getLocalBounds().height / 2);
        txt.setPosition(xPos, yPos);
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // You can draw other high-level objects
        target.draw(txt, states);

    }
};

