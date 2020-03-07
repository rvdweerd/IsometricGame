#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile() = default;
	Tile(const sf::Sprite&, const sf::Sprite&, const sf::Vector2f& pos);
	void Draw(sf::RenderWindow& window);
	void SetHighlighted(bool flag);
private:
	bool isHighlighted;
	sf::Sprite tile;
	sf::Sprite tile_hl;
};