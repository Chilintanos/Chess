#include "GameManager.h"
#include <iostream>

void GameManager::draw_field() {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			sf::Color color;
			if ((x + y) % 2 == 0) {
				color = field_cell_color1;
			}
			else {
				color = field_cell_color2;
			}
			draw_tile({ y,x }, color);
		}
	}
}

void GameManager::change_turn() {
	if (current_turn_color == black)black_time -= decrease_time;
	if (current_turn_color == white)white_time -= decrease_time;
	current_turn_color = reverse_color(current_turn_color);
	Field an;
	an.figures = std::vector<Figure>(figures);
	if (an.is_mate(current_turn_color)) {
		win(reverse_color(current_turn_color));
	}

}

void GameManager::turn_to(std::pair<int, int> position) {
	reserved_turn = std::vector<Figure>(figures);
	reserved_turn_color = current_turn_color;
	auto selfigind = get_selected_index();
	if (selfigind != -1) {
		int tempi = get_figure_index(position);
		if (tempi != -1) {
			figures.erase(figures.begin() + tempi);
		}
		selfigind = get_selected_index();
		figures[selfigind].set_position(position);
		reset_chsn_and_turns();
	}
	change_turn();
}

void GameManager::draw_tile(std::pair<int, int> position, sf::Color color) {
	sf::RectangleShape rect(sf::Vector2f(cell_size, cell_size));
	rect.setFillColor(color);
	rect.setPosition(sf::Vector2f(field_start_pos.first + position.first * cell_size, field_start_pos.second + position.second * cell_size));
	window.draw(rect);
}

bool GameManager::on_mouse_in_tile(std::pair<int, int> position) {
	int mouse_x = sf::Mouse::getPosition(window).x;
	int mouse_y = sf::Mouse::getPosition(window).y;
	int start_pos_x = field_start_pos.first + position.first * cell_size;
	int start_pos_y = field_start_pos.second + position.second * cell_size;
	int end_pos_x = field_start_pos.first + (position.first + 1) * cell_size;
	int end_pos_y = field_start_pos.second + (position.second + 1) * cell_size;
	if (mouse_x > start_pos_x && mouse_x < end_pos_x && mouse_y > start_pos_y && mouse_y < end_pos_y) {
		return true;
	}
	return false;
}

void GameManager::mouse_clicked() {
	for (int i = 0; i < turns.size(); i++) {
		if( on_mouse_in_tile(turns[i])) {
			turn_to(turns[i]);
			return;
		}
	}
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].is_mouse_over(window) && figures[i].get_color() == current_turn_color) {
			reset_chsn_and_turns();
			figures[i].is_choosen = true;
			make_turns(figures[i], current_turn_color);
			return;
		}
	}
}

void  GameManager::set_figures_texture_color(figurecolor fig_color, sf::Color color) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].get_color() == fig_color) {
			figures[i].set_texture_color(color);
		}
	}
}

void GameManager::set_figures_cell_size(int size) {
	for (int i = 0; i < figures.size(); i++) {
		figures[i].own_cell_size = size;
	}
}

void GameManager::Step() {

	sf::Event event;
	sf::Font font;
	font.loadFromFile("fonts/ArialRegular.ttf");

	sf::Text white_turn(sf::String("Your turn"), font, 20u);
	white_turn.setPosition(sf::Vector2f(25, 500));

	sf::Text black_turn(sf::String("Your turn"), font, 20u);
	black_turn.setPosition(sf::Vector2f(25, 75));

	sf::Text white_win(sf::String("White side win"), font, 60u);
	white_win.setPosition(sf::Vector2f(40, 225));

	sf::Text black_win(sf::String("Black side win"), font, 60u);
	black_win.setPosition(sf::Vector2f(40, 225));

	SimpleButton cancel_move_button(sf::Vector2f(450, 450), sf::Vector2f(200, 50), sf::String("Cancel a move"), font, 20u);
	buttons.push_back(&cancel_move_button);
	SimpleButton surrender_black_button(sf::Vector2f(25, 15), sf::Vector2f(100, 50), sf::String("Surrender"), font, 20u);
	buttons.push_back(&surrender_black_button);
	SimpleButton surrender_white_button(sf::Vector2f(25, 535), sf::Vector2f(100, 50),  sf::String("Surrender"), font, 20u);
	buttons.push_back(&surrender_white_button);
	sf::Text start_text(sf::String("Start:"), font, 20u);
	start_text.setPosition(sf::Vector2f(790, 420));

	//timers
	SimpleButton button_x(sf::Vector2f(790, 450), sf::Vector2f(50, 50), sf::String("X"), font, 10u);
	buttons.push_back(&button_x);
	SimpleButton button_55(sf::Vector2f(850, 450), sf::Vector2f(50, 50), sf::String("5m+5s"), font, 10u);
	buttons.push_back(&button_55);
	SimpleButton button_510(sf::Vector2f(910, 450), sf::Vector2f(50, 50), sf::String("10m+5s"), font, 10u);
	buttons.push_back(&button_510);
	sf::Text black_timer(sf::String(""), font, 20u);
	black_timer.setPosition(sf::Vector2f(350, 25));

	sf::Text white_timer(sf::String(""), font, 20u);
	white_timer.setPosition(sf::Vector2f(350, 525));
	
	sf::Text col_fig_text(sf::String("Figure's colors:"), font, 20u);
	col_fig_text.setPosition(sf::Vector2f(450, 100));

	sf::Text col_field_text(sf::String("Tile's colors:"), font, 20u);
	col_field_text.setPosition(sf::Vector2f(450, 200));

	sf::Text size_text(sf::String("Field size:"), font, 20u);
	size_text.setPosition(sf::Vector2f(450, 300));

	SimpleButton big_button(sf::Vector2f(650, 285), sf::Vector2f(50, 50), sf::String(""), font, 20u);
	buttons.push_back(&big_button);
	SimpleButton mid_button(sf::Vector2f(710, 285), sf::Vector2f(35, 35), sf::String(""), font, 20u);
	buttons.push_back(&mid_button);
	SimpleButton lil_button(sf::Vector2f(755, 285), sf::Vector2f(25, 25), sf::String(""), font, 20u);
	buttons.push_back(&lil_button);

	color_rect_changer col_fig_rec_chngr2(sf::Vector2f(650, 85), sf::Vector2f(50, 50), figure_colors, sf::Color::White);
	color_rect_changer col_fig_rec_chngr1(sf::Vector2f(710, 85), sf::Vector2f(50, 50), figure_colors, sf::Color::Black);
	set_figures_texture_color(black, col_fig_rec_chngr1.current_value);
	set_figures_texture_color(white, col_fig_rec_chngr2.current_value);

	color_rect_changer col_field_rec_chngr1(sf::Vector2f(650, 185), sf::Vector2f(50, 50), field_cell_colors, sf::Color::Black);
	color_rect_changer col_field_rec_chngr2(sf::Vector2f(710, 185), sf::Vector2f(50, 50), field_cell_colors, col_field_rec_chngr1.current_value);
	field_cell_color1 = col_field_rec_chngr1.current_value;
	field_cell_color2 = col_field_rec_chngr2.current_value;

	reserved_turn = std::vector<Figure>(figures);

	set_figures_texture_color(black, col_fig_rec_chngr1.current_value);
	set_figures_texture_color(white, col_fig_rec_chngr2.current_value);

	while (window.isOpen()) {

		cur_frame = time(NULL);
		if (current_turn_color == black)black_time += cur_frame - prev_frame;
		if (current_turn_color == white)white_time += cur_frame - prev_frame;
		prev_frame = cur_frame;

		
		while (window.pollEvent(event))
		{
			for (int i = 0; i < buttons.size(); i++) {
				if (buttons[i]->is_mouse_on(window)) {
					buttons[i]->do_mouse_on();
				}
				else {
					buttons[i]->do_calm();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (col_fig_rec_chngr1.is_mouse_on(window)) {
					col_fig_rec_chngr1.next();
					col_fig_rec_chngr2.opposite_color = col_fig_rec_chngr1.current_value;
					set_figures_texture_color(black, col_fig_rec_chngr1.current_value);
				}
				if (col_fig_rec_chngr2.is_mouse_on(window)) {
					col_fig_rec_chngr2.next();
					col_fig_rec_chngr1.opposite_color = col_fig_rec_chngr2.current_value;
					set_figures_texture_color(white, col_fig_rec_chngr2.current_value);
				}
				if (col_field_rec_chngr1.is_mouse_on(window)) {
					col_field_rec_chngr1.next();
					col_field_rec_chngr2.opposite_color = col_field_rec_chngr1.current_value;
					field_cell_color1 = col_field_rec_chngr1.current_value;
				}
				if (col_field_rec_chngr2.is_mouse_on(window)) {
					col_field_rec_chngr2.next();
					col_field_rec_chngr1.opposite_color = col_field_rec_chngr2.current_value;
					field_cell_color2 = col_field_rec_chngr2.current_value;
				}
				if (big_button.is_mouse_on(window)) {
					set_figures_cell_size(50);
					current_cell_size = 50;
					cell_size = 50;
					big_button.do_pressed();
				}
				if (mid_button.is_mouse_on(window)) {
					set_figures_cell_size(40);
					current_cell_size = 40;
					cell_size = 40;
					mid_button.do_pressed();
				}
				if (lil_button.is_mouse_on(window)) {
					set_figures_cell_size(30);
					current_cell_size = 30;
					cell_size = 30;
					lil_button.do_pressed();
				}
				if (cancel_move_button.is_mouse_on(window)) {
					turn_turn_back();
					cancel_move_button.do_pressed();
				}
				if (button_x.is_mouse_on(window)) {
					reset();
					button_x.do_pressed();
				}
				if (button_55.is_mouse_on(window)) {
					reset();
					is_timer = true;
					target_time = 5 * 60;
					decrease_time = 5;
					button_55.do_pressed();
				}
				if (button_510.is_mouse_on(window)) {
					reset();
					is_timer = true;
					target_time = 10 * 60;
					decrease_time = 5;
					button_510.do_pressed();
				}

				if (who_win == color_none) {
					if (surrender_black_button.is_mouse_on(window)) {
						win(black);
						surrender_black_button.do_pressed();
					}
					if (surrender_white_button.is_mouse_on(window)) {
						win(white);
						surrender_white_button.do_pressed();
					}
					mouse_clicked();
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Figure testPawn(pawn, white);
		//testPawn.set_position({ 2, 2 });
		window.clear(field_background_color);



		//testPawn.draw(window);
		draw_field();
		draw_turns();
		draw_figures();
		window.draw(col_fig_text);
		window.draw(col_field_text);
		window.draw(col_fig_rec_chngr1);
		window.draw(col_fig_rec_chngr2);
		window.draw(col_field_rec_chngr1);
		window.draw(col_field_rec_chngr2);
		window.draw(size_text);
		window.draw(lil_button);
		window.draw(mid_button);
		window.draw(big_button);
		window.draw(cancel_move_button);
		window.draw(surrender_black_button);
		window.draw(surrender_white_button);
		window.draw(start_text);
		window.draw(button_x);
		window.draw(button_510);
		window.draw(button_55);
		if (is_timer) {
			if (target_time - black_time <= 0)win(white);
			if (target_time - white_time <= 0)win(black);
			black_timer.setString(std::to_string(int(target_time - black_time)));
			window.draw(black_timer);
			white_timer.setString(std::to_string(int(target_time - white_time)));
			window.draw(white_timer);
		}
		if(current_turn_color == white)
			window.draw(white_turn);
		if (current_turn_color == black)
			window.draw(black_turn);
		if(who_win == white)
			window.draw(black_win);
		if (who_win == black)
			window.draw(white_win);

		window.display();
	}
}

void GameManager::win(figurecolor color) {
	who_win = color;
	reset_chsn_and_turns();
}

bool GameManager::is_window_open() {
	return window.isOpen();
}

void GameManager::turn_turn_back() {
	who_win = color_none;
	figures = std::vector<Figure>(reserved_turn);
	current_turn_color = reserved_turn_color;
}

void GameManager::init_field() {

	for (int i = 0; i < 8; i++) {
		Figure temp(field_preset[i], black);
		temp.set_position({ i, 0 });
		figures.push_back(temp);
	}
	for (int i = 0; i < 8; i++) {
		Figure temp(pawn, black);
		temp.set_position({ i, 1 });
		figures.push_back(temp);
	}
	for (int i = 0; i < 8; i++) {
		Figure temp(field_preset[i], white);
		temp.set_position({ i, 7 });
		figures.push_back(temp);
	}
	for (int i = 0; i < 8; i++) {
		Figure temp(pawn, white);
		temp.set_position({ i, 6 });
		figures.push_back(temp);
	}
}

void GameManager::draw_turns() {
	for (int i = 0; i < turns.size(); i++) {
		draw_tile(turns[i], field_turn_color);
	}
}

void GameManager::draw_figures() {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].is_choosen) {
			draw_tile(figures[i].get_position(), field_choosen_color);
		}
		if (figures[i].get_name() == king){
			Field an;
			an.figures = std::vector<Figure>(figures);
			if (an.is_check(figures[i].get_color()))draw_tile(figures[i].get_position(), check_color);
		}
		figures[i].draw(window);

	}
}