#include "Tile.h"

Tile::Tile(const sf::Sprite& tileSprite, const sf::Sprite& tileSprite_hl, const sf::Vector2f& pos)
	:
	tile(tileSprite),
	tile_hl(tileSprite_hl),
	isHighlighted(false)
{
	tile.setPosition(pos);
	tile_hl.setPosition(pos);
}

void Tile::Draw(sf::RenderWindow& window)
{
	if (isHighlighted)
	{
		window.draw(tile_hl);
		isHighlighted = false;
	}
	else
	{
		window.draw(tile);
	}
}

void Tile::SetHighlighted(bool flag)
{
	isHighlighted = flag;
}
