#include "resources.h"
#include "figure.h"
#include <SFML/Graphics.hpp>
#pragma once
struct Field
{
	/*!
	 * \brief Checks for the presence of a king of a given color in adjacent cells
	 */
	bool is_king_nearby(figurecolor which_one, std::pair<int, int> position);
	/*!
	 * \brief Vector of all possible moves of the selected figure
	 */
	std::vector<std::pair<int, int>> turns;
	/*!
	 * \brief Create a vector of all possible moves of the selected figure
	 */
	void make_turns(Figure figure, figurecolor current_turn_color);
	/*!
	 * \brief Create a vector of all possible moves of the selected figure withou checking on check
	 */
	void simple_make_turns(Figure figure, figurecolor current_turn_color);
	/*!
	 * \brief reset turns and choosen
	 */
	void reset_chsn_and_turns();
	/*!
	 * \brief vector of all figures
	 */
	std::vector<Figure> figures;
	/*!
	 * \brief retrieves figures from a given position
	 */
	Figure get_figure(std::pair<int, int> position);
	/*!
	 * \brief retrieves choosen figure
	 */
	Figure get_selected();
	/*!
	 * \brief checks whether the figure is on the field
	 */
	bool is_in_field(std::pair<int, int> coord);
	/*!
	 * \brief retrieves index of choosen figure
	 */
	int get_selected_index();
	/*!
	 * \brief retrieves index of figures from a given position
	 */
	int get_figure_index(std::pair<int, int> position);
	/*!
	 * \brief deletes a shape at a given position
	 */
	bool delete_at(std::pair<int, int> position);
	/*!
	 * \brief checks on the check
	 */
	bool is_check(figurecolor to_whom);
	/*!
	 * \brief checks for a checkmate
	 */
	bool is_mate(figurecolor to_whom);
	/*!
	 * \brief getting the king of a given color
	 */
	Figure get_king(figurecolor which_one);
	/*!
	 * \brief getting the index of king of a given color
	 */
	int get_king_index(figurecolor which_one);
	/*!
	 * \brief checks on the check in given position
	 */
	bool check_check(figurecolor to_whom, std::pair<int, int> from_pos, std::pair<int, int> to_pos);
};

