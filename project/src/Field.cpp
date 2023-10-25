#include "Field.h"
Figure Field::get_figure(std::pair<int, int> position) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].get_position() == position)
			return figures[i];
	}
	return Figure(none, white);
}

bool Field::is_in_field(std::pair<int, int> coord) {
	if (coord.first >= 0 && coord.first < 8 && coord.second >= 0 && coord.second < 8)
		return true;
	return false;
}

int Field::get_figure_index(std::pair<int, int> position) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].get_position() == position)
			return i;
	}
	return -1;
}

Figure Field::get_selected() {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].is_choosen)
			return figures[i];
	}
	return Figure(none, white);
}

int Field::get_selected_index() {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].is_choosen)
			return i;
	}
	return -1;
}

bool Field::delete_at(std::pair<int, int> position) {
	int tempi = get_figure_index(position);
	if (tempi != -1) {
		figures.erase(figures.begin() + tempi);
		return true;
	}
	return false;
}

bool Field::is_king_nearby(figurecolor which_one, std::pair<int, int> position) {
	std::vector<std::pair<int, int>> temp = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (int i = 0; i < 8; i++) {
		if (is_in_field(position + temp[i]) && get_figure(position + temp[i]).get_name() == king && get_figure(position + temp[i]).get_color() == which_one)return true;
	}
	return false;
}

bool Field::check_check(figurecolor to_whom, std::pair<int, int> from_pos, std::pair<int, int> to_pos) {
	Field an;
	an.figures = std::vector<Figure>(figures);
	an.delete_at(to_pos);
	an.figures[an.get_figure_index(from_pos)].set_position(to_pos);
	return an.is_check(to_whom);
}

void Field::simple_make_turns(Figure figure, figurecolor current_turn_color) {
	auto step_conf = figure.get_step_conf();
	auto take_conf = figure.get_take_step_conf();
	auto line_conf = figure.get_line_step_conf();
	auto take_line_conf = figure.get_take_line_step_conf();

	for (int i = 0; i < step_conf.size(); i++) {
		auto pos = figure.get_position() + step_conf[i];
		if (is_in_field(pos)) {
			if (get_figure(pos).get_name() == none) {
			
					turns.push_back(pos);
			}
		}
	}

	for (int i = 0; i < take_conf.size(); i++) {
		auto pos = figure.get_position() + take_conf[i];
		if (is_in_field(pos)) {
			auto temp = get_figure(pos);
			if (temp.get_name() != none && temp.get_color() == reverse_color(figure.get_color())) {
			
					turns.push_back(pos);
			}
		}
	}

	for (int i = 0; i < line_conf.size(); i++) {
		auto pos = figure.get_position() + line_conf[i];
		while (is_in_field(pos)) {
			if (get_figure(pos).get_name() == none) {
				
				
						turns.push_back(pos);
			}
			else
			{
				if (get_figure(pos).get_color() == reverse_color(figure.get_color())) {
				
						turns.push_back(pos);
				}
				break;
			}
			pos = pos + line_conf[i];
		}
	}
}

void Field::make_turns(Figure figure, figurecolor current_turn_color) {
	auto step_conf = figure.get_step_conf();
	auto take_conf = figure.get_take_step_conf();
	auto line_conf = figure.get_line_step_conf();
	auto take_line_conf = figure.get_take_line_step_conf();


	for (int i = 0; i < step_conf.size(); i++) {
		auto pos = figure.get_position() + step_conf[i];
		if (is_in_field(pos)) {
			if (get_figure(pos).get_name() == none) {
				if (!check_check(current_turn_color, figure.get_position(), pos))
					if (!(figure.get_name() == king && is_king_nearby(reverse_color(current_turn_color), pos)))
					turns.push_back(pos);
			}
		}
	}

	for (int i = 0; i < take_conf.size(); i++) {
		auto pos = figure.get_position() + take_conf[i];
		if (is_in_field(pos)) {
			auto temp = get_figure(pos);
			if (temp.get_name() != none && temp.get_color() == reverse_color(figure.get_color())) {
				if (!check_check(current_turn_color, figure.get_position(), pos))
					if (!(figure.get_name() == king && is_king_nearby(reverse_color(current_turn_color), pos)))
					turns.push_back(pos);
			}
		}
	}

	for (int i = 0; i < line_conf.size(); i++) {
		auto pos = figure.get_position() + line_conf[i];
		while (is_in_field(pos)) {
			if (get_figure(pos).get_name() == none) {
				if (!check_check(current_turn_color, figure.get_position(), pos))
					if (!check_check(current_turn_color, figure.get_position(), pos))
						if (!(figure.get_name() == king && is_king_nearby(reverse_color(current_turn_color), pos)))
						turns.push_back(pos);
			}
			else
			{
				if (get_figure(pos).get_color() == reverse_color(figure.get_color())) {
					if (!check_check(current_turn_color, figure.get_position(), pos))
						if (!(figure.get_name() == king && is_king_nearby(reverse_color(current_turn_color), pos)))
						turns.push_back(pos);
				}
				break;
			}
			pos = pos + line_conf[i];
		}
	}
}

void Field::reset_chsn_and_turns() {
	for (int i = 0; i < figures.size(); i++) {
		figures[i].is_choosen = false;
	}
	turns.clear();
}

bool Field::is_check(figurecolor to_whom) {
	reset_chsn_and_turns();
	auto king = get_king(to_whom);
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].get_color() == reverse_color(to_whom))
			simple_make_turns(figures[i], reverse_color(to_whom));
	}
	if (std::find(turns.begin(), turns.end(), king.get_position()) != turns.end()) {
		return true;
	}
	return false;
}

bool Field::is_mate(figurecolor to_whom) {
	reset_chsn_and_turns();
	auto king = get_king(to_whom);
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].get_color() == (to_whom))
			make_turns(figures[i], (to_whom));
	}
	if (turns.size() == 0) {
		if (is_check(to_whom))return true;
		else return false;
	}
	return false;
}

Figure Field::get_king(figurecolor which_one) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].get_name() == king)
			return figures[i];
	}
	return Figure(none, white);
}

int Field::get_king_index(figurecolor which_one) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].get_name() == king)
			return i;
	}
	return -1;
}