#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

struct Tile
{
	Tile(const sf::Texture& tex,const sf::Texture& tex_hl)
		:
		tex(tex),
		tex_hl(tex_hl),
		isHighlighted(false),
		tile(tex)
	{
	}
	void Draw(sf::RenderWindow& window)
	{
		if (isHighlighted)
		{
			tile.setTexture(tex_hl);
			window.draw(tile);
			isHighlighted = false; 
			tile.setTexture(tex);
		}
		else
		{
			window.draw(tile);
		}
	}
	sf::Texture tex;
	sf::Texture tex_hl;
	bool isHighlighted;
	sf::Sprite tile;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,600),"Isomeric Game");
	sf::Texture tileTex;
	sf::Texture tileTexHL;
	if (!tileTex.loadFromFile("resources/tile.png"))
	{
		return -1;
	}
	if (!tileTexHL.loadFromFile("resources/tile_hl.png"))
	{
		return -1;
	}
	
	std::vector<std::vector<Tile>> tiles;
	const unsigned width = 800 / 32;
	const unsigned height = 600 / 32;
	for (size_t x = 0; x < width; x++)
	{
		std::vector<Tile> v;
		for (size_t y = 0; y < height; y++)
		{
			Tile t(tileTex, tileTexHL);
			t.tile.setPosition((float)x * 32,(float)y * 32);
			v.push_back(t);
		}
		tiles.push_back(v);
	}

	while (window.isOpen())
	{
		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		std::cout << "Mouse: (" << pos.x << "," << pos.y << ")\n";
		int hoverX = pos.x / 32;
		int hoverY = pos.y / 32;
		if (hoverX >= 0 && hoverY >= 0 && hoverX < width && hoverY < height)
		{
			tiles[hoverX][hoverY].isHighlighted=true;
		}

		for (size_t x = 0; x < width; x++)
		{
			for (size_t y = 0; y < height; y++)
			{
				tiles[x][y].Draw(window);
			}
		}

		window.display();
	}
	return 0;
}