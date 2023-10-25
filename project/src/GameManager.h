#include "resources.h"
#include "figure.h"
#include "Field.h"
#include "color_rect_changer.h"
#include "SimpleButton.h"
#include <ctime>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <stdio.h>
#pragma once
class GameManager : Field
{
private:
	int current_cell_size;
	bool is_timer;
	time_t start_time;
	time_t black_time;
	time_t white_time;
	time_t prev_frame;
	time_t cur_frame;
	time_t target_time;
	time_t decrease_time;
	bool is_game_ends;
	std::vector<Figure> reserved_turn;
	figurecolor reserved_turn_color;
	figurecolor who_win;
	bool is_playing;
	figurecolor current_turn_color;
	sf::RenderWindow window;
	void win(figurecolor color);
	void draw_field();
	void turn_turn_back();
	void turn_to(std::pair<int, int> position);
	bool is_have_check(std::vector<Figure> _figures, figurecolor color);
	void init_field();
	void draw_figures();
	void draw_turns();
	void change_turn();
	void draw_tile(std::pair<int, int>, sf::Color);
	void mouse_clicked();

	bool on_mouse_in_tile(std::pair<int, int> position);
	void set_figures_texture_color(figurecolor fig_color, sf::Color color);
	void set_figures_cell_size(int size);

	void reset() {
		is_timer = false;
		black_time = 0;
		white_time = 0;
		target_time = 0;
		decrease_time = 0;
		cur_frame = time(NULL);
		start_time = time(NULL);
		figures.clear();
		who_win = color_none;
		is_game_ends = false;
		current_turn_color = black;
		reserved_turn_color = current_turn_color;
		init_field();
		set_figures_cell_size(current_cell_size);
	}
public:
	GameManager() {
		current_cell_size = 50;
		reset();
		window.create(sf::VideoMode(windowsize.first, windowsize.second), window_name, sf::Style::Default);
	}
	
	/*!
	 * \check on windows is open
	 */
	bool is_window_open();
	/*!
	 * \brief one frame of game
	 */
	void Step();
};

