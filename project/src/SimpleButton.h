#include <SFML/Graphics.hpp>
#include "CenteredText.h"
#pragma once
class SimpleButton : public sf::Drawable
{ 
public:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape rect;
    CenteredText txt;
    const sf::Color calm;
    const sf::Color mouse_on;
    const sf::Color pressed;
    void do_calm() {
        rect.setFillColor(calm);
    }
    void do_mouse_on() {
        rect.setFillColor(mouse_on);
    }
    void do_pressed() {
        rect.setFillColor(pressed);
    }
    SimpleButton(sf::Vector2f _position, sf::Vector2f _size, sf::String _text, sf::Font& _font, unsigned int _font_size)
        : txt(_position, _size, _text, _font, _font_size), calm(128, 128, 128), mouse_on(108, 108, 108), pressed(88, 88, 88)
    {
        position = _position;
        size = _size;
        rect.setPosition(position);
        rect.setSize(size);
       
        do_calm();
    }

    bool is_mouse_on(sf::RenderWindow& window) {
        int mouse_x = sf::Mouse::getPosition(window).x;
        int mouse_y = sf::Mouse::getPosition(window).y;
        int start_pos_x = position.x;
        int start_pos_y = position.y;
        int end_pos_x = position.x + size.x;
        int end_pos_y = position.y + size.y;
        if (mouse_x > start_pos_x && mouse_x < end_pos_x && mouse_y > start_pos_y && mouse_y < end_pos_y) {
            return true;
        }
        return false;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {

        // You can draw other high-level objects
        target.draw(rect, states);
        target.draw(txt, states);
    }
};

