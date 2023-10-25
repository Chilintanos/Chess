#include <vector>
#include <SFML/Graphics.hpp>
#include "resources.h"
#pragma once
class Figure
{
private:
	std::pair<int, int> position;
	sf::Texture texture;
	sf::Color texture_color;
	sf::Sprite sprite;
	figurenames name;
	figurecolor color;
	std::vector<std::pair<int, int>> step_conf;
	std::vector<std::pair<int, int>> take_step_conf;
	std::vector<std::pair<int, int>> line_step_conf;
	std::vector<std::pair<int, int>> take_line_step_conf;
	void set_texture();
	void pawn_conf();
public:
	/*!
	 * \brief is figure choosen
	 */
	bool is_choosen;
	/*!
	 * \brief cell size of figure
	 */
	int own_cell_size;
	Figure(figurenames _name,
		figurecolor _color);
	/*!
	 * \brief get name
	 */
	figurenames get_name();
	/*!
	 * \brief set color of figure's texture
	 */
	void set_texture_color(sf::Color color);
	/*!
	 * \brief get color of figure's texture
	 */
	figurecolor get_color();
	/*!
	 * \brief get configuration of one step
	 */
	std::vector<std::pair<int, int>> get_step_conf();
	/*!
	 * \brief get configuration of take in one step
	 */
	std::vector<std::pair<int, int>> get_take_step_conf();
	/*!
	 * \brief get configuration on lines steps
	 */
	std::vector<std::pair<int, int>> get_line_step_conf();
	/*!
	 * \brief get configuration on take in lines steps
	 */
	std::vector<std::pair<int, int>> get_take_line_step_conf();
	/*!
	 * \brief get position
	 */
	std::pair<int, int> get_position();
	/*!
	 * \brief set position
	 */
	void set_position(std::pair<int, int> _position);
	/*!
	 * \brief draw
	 */
	void draw(sf::RenderWindow& window);
	/*!
	 * \brief check is mouse over figure
	 */
	bool is_mouse_over(sf::RenderWindow& window);
};

