#include "figure.h"
void Figure::set_texture() {
	texture.loadFromFile(figure_textures_paths[name]);
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(own_cell_size /100.0, own_cell_size /100.0));
}
void Figure::set_texture_color(sf::Color color) {
	sprite.setColor(color);
}

void Figure::pawn_conf() {
	step_conf.clear();
	take_step_conf.clear();
	int dir_y = (color == black ? 1 : -1);
	int is_two = (position.second == (color == black ? 1 : 6));
	step_conf.push_back({ 0, dir_y });
	if (is_two)step_conf.push_back({ 0, dir_y * 2 });
	take_step_conf.push_back({ 1, dir_y });
	take_step_conf.push_back({ -1, dir_y });
}

	Figure::Figure(figurenames _name,
		figurecolor _color) {
		name = _name;
		color = _color;
		is_choosen = false;
		texture_color = figure_color_and_texture_color_matcher[color];
		own_cell_size = cell_size;
		if (name == pawn) {
			pawn_conf();
		}
		else {
			step_conf = step_configurations[name];
			line_step_conf = line_step_configurations[name];
			take_step_conf = step_configurations[name];
			take_line_step_conf = line_step_configurations[name];
		}

	}

	figurenames Figure::get_name() {
		return name;
	}

	figurecolor Figure::get_color() {
		return color;
	}

	std::vector<std::pair<int, int>> Figure::get_step_conf() {
		return step_conf;
	}

	std::vector<std::pair<int, int>> Figure::get_take_step_conf() {
		return take_step_conf;
	}

	std::vector<std::pair<int, int>> Figure::get_line_step_conf() {
		return line_step_conf;
	}

	std::vector<std::pair<int, int>> Figure::get_take_line_step_conf() {
		return take_line_step_conf;
	}

	std::pair<int, int> Figure::get_position() {
		return position;
	}

	void Figure::set_position(std::pair<int, int> _position) {
		position = _position;
		if (name == pawn) {
			pawn_conf();
		}
	}

	void Figure::draw(sf::RenderWindow& window) {
		set_texture();
		sprite.setPosition(sf::Vector2f(field_start_pos.first + position.first * own_cell_size, field_start_pos.second + position.second * own_cell_size));
		window.draw(sprite);
	}

	bool Figure::is_mouse_over(sf::RenderWindow& window) {
		int mouse_x = sf::Mouse::getPosition(window).x;
		int mouse_y = sf::Mouse::getPosition(window).y;
		int start_pos_x = field_start_pos.first + position.first * own_cell_size;
		int start_pos_y = field_start_pos.second + position.second * own_cell_size;
		int end_pos_x = field_start_pos.first + (position.first + 1) * own_cell_size;
		int end_pos_y = field_start_pos.second + (position.second + 1) * own_cell_size;
		if (mouse_x > start_pos_x && mouse_x < end_pos_x && mouse_y > start_pos_y && mouse_y < end_pos_y) {
			return true;
		}
		return false;
	}