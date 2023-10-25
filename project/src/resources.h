#pragma once
#include <map>
#include <SFML/Graphics.hpp>

#ifndef CONSTANTS_H
#define CONSTANTS_H

static enum figurenames { none, pawn, king, knight, queen, bishop, rook };
static enum figurecolor { black, white, color_none };

static const std::pair<int, int> windowsize = {1000, 600};
static int cell_size = 50;
static const std::pair<int, int> field_start_pos = { 25, 100 };

static sf::Color check_color = sf::Color::Red;
static sf::Color field_cell_color1 = sf::Color(200, 200, 200);
static sf::Color field_cell_color2 = sf::Color(75, 75, 75);
static const std::vector<sf::Color> field_cell_colors = { sf::Color(200, 200, 200), sf::Color(75, 75, 75), sf::Color(90, 0, 0), sf::Color(0, 90, 0), sf::Color(0, 0, 90)};
static sf::Color field_choosen_color = sf::Color(255, 242, 0, 100);
static sf::Color field_turn_color = sf::Color(50, 242, 50, 100);
static sf::Color field_background_color = sf::Color(150, 150, 150);

static std::string window_name = "Chess";

static std::string textures_path = "textures\\";
static std::map<figurenames, std::string> figure_textures_paths ={ 
	{pawn, textures_path+"pawn.png"},
	{king, textures_path + "king.png"},
	{knight, textures_path + "knight.png"},
	{queen, textures_path + "queen.png"},
	{bishop, textures_path + "bishop.png"},
	{rook, textures_path + "rook.png"}
};

static std::map<figurecolor, sf::Color> figure_color_and_texture_color_matcher = {
	{black, sf::Color::White},
	{white, sf::Color::Black}
};
static const std::vector<sf::Color> figure_colors = { sf::Color::Black, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan, sf::Color::White };

static std::vector<figurenames> field_preset = { rook, knight, bishop, queen, king, bishop, knight, rook };

static figurecolor reverse_color(figurecolor color) {
	if (color == black) {
		return white;
	}
	return black;
}

static std::map<figurenames, std::vector<std::pair<int, int>>> step_configurations = {
	{knight, {{2,1},{1,2},{-1,2},{2,-1},{1, -2},{-2, 1},{-1, -2}, {-2, -1}}},
	{king, {{1,0},{1,1},{0,1},{-1,0},{-1,1},{0,-1},{-1,-1},{1, -1}}}
};

static std::map<figurenames, std::vector<std::pair<int, int>>> line_step_configurations = {
	{rook, {{1,0},{0,1},{-1,0},{0,-1}}},
	{queen, {{1,0},{1,1},{0,1},{-1,0},{-1,1},{0,-1},{-1,-1},{1, -1}}},
	{bishop, {{1,1},{-1,1}, {1,-1}, {-1, -1}}}
};

static std::pair<int, int> operator+(std::pair<int, int> a, std::pair<int, int> b) {
	return { a.first + b.first, a.second + b.second };
}

static std::pair<int, int> operator-(std::pair<int, int> a, std::pair<int, int> b) {
	return { a.first - b.first, a.second - b.second };
}

static bool operator==(std::pair<int, int> a, std::pair<int, int> b) {
	return (a.first == b.first && a.second == b.second);
}

#endif