#include <SFML/Graphics.hpp>
#pragma once
class color_rect_changer : public sf::Drawable
{
public:
    int current_ind;
	sf::Vector2f position;
	sf::Vector2f size;
    sf::Color current_value;
    std::vector<sf::Color> color_array;
    sf::Color opposite_color;
    sf::RectangleShape rect;

    color_rect_changer(sf::Vector2f _position, sf::Vector2f _size, std::vector<sf::Color> _color_array, sf::Color _opposite_color) : color_array(_color_array) {
        position = _position;
        size = _size;
        opposite_color = _opposite_color;
        current_ind = 0;
        rect.setPosition(position);
        rect.setSize(size);
        next();
        prev();
        rect.setFillColor(current_value);
    }

    void next() {
        while (true) {
            current_ind++;
            if (current_ind >= color_array.size()) {
                current_ind = 0;
            }
            current_value = color_array[current_ind];
            if (current_value != opposite_color)break;
        }
        rect.setFillColor(current_value);
    }

    void prev() {
        while (true) {
            current_ind--;
            if (current_ind < 0) {
                current_ind = color_array.size()-1;
            }
            current_value = color_array[current_ind];
            if (current_value != opposite_color)break;
        }
        rect.setFillColor(current_value);
    }

    bool is_mouse_on(sf::RenderWindow &window) {
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
        target.draw(rect , states);

    }
};

