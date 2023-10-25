#include <SFML/Graphics.hpp>
#pragma once
class SimpleButton : public sf::Drawable
{
public:
    int current_ind;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape rect;

    SimpleButton(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color) {
        position = _position;
        size = _size;
        rect.setPosition(position);
        rect.setSize(size);
        rect.setFillColor(_color);
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
        target.draw(rect, states);
    }
};

