// Exteral libraries includes
#include <SFML/Graphics.hpp>
#include <PUGUXML/pugixml.hpp>
// STL includes
#include <vector>
#include <iostream>
// Own header file includes
#include "Tile.h"
#include "SpriteFactory.h"

sf::Vector2f Flat2Iso(const sf::Vector2f& p)
{
	float x0 = (float) p.x;
	float y0 = (float) p.y;
	int t_x = (int)p.x / 32;
	int t_y = (int)p.y / 32;
	float p0_x = x0 - t_x * 32.0f;
	float p0_y = y0 - t_y * 32.0f;
	float p1_x = 1.414f * p0_x;
	float p1_y = 1.414f * p0_y;
	float p2_x = (0.707f * p1_x - 0.707 * p1_y);
	float p2_y = (-0.707f * p1_x + 0.707 * p1_y);
	float p3_x = p2_x;
	float p3_y = p2_y * 0.5f;
	float p4_x = p3_x + t_x * 32.0f - t_y * 32.0f-32 +380;
	float p4_y = p3_y + t_x * 16.0f + t_y * 16.0f +100;
	return { p4_x,p4_y };
}

sf::Vector2f Iso2Flat(const sf::Vector2f& p)
{
	float a = 32.0f; float b = -32.0f; float c = 16.0f; float d = 16.0f;
	float det = (a * d - b * c);
	float t = d / det; float u = -b / det; float v = -c / det; float w = a / det;
	float xt = t * (p.x - 380) + u * (p.y - 100);
	float yt = v * (p.x - 380) + w * (p.y - 100);
	return { xt*32.0f , yt*32.0f };
}

int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("resources/examplemap.tmx");
	if (result.status != pugi::xml_parse_status::status_ok)
	{
		return -1;
	}
	printf("Element name: %s",doc.name());

	sf::RenderWindow window(sf::VideoMode(800,600),"Isomeric Game");
	
	SpriteFactory factory;
	unsigned int tile = factory.LoadTexture("resources/iso_tile.png");
	unsigned int tile_hl = factory.LoadTexture("resources/iso_tile_hl.png");

	std::vector<std::vector<Tile>> tiles;
	const unsigned width = 10;
	const unsigned height = 10;
	for (size_t x = 0; x < width; x++)
	{
		std::vector<Tile> v;
		for (size_t y = 0; y < height; y++)
		{
			//Tile t(factory.GetSprite(tile), factory.GetSprite(tile_hl), { x * 32.0f-y*32.0f, x * 16.0f +y*16.0f });			
			Tile t(factory.GetSprite(tile), factory.GetSprite(tile_hl), Flat2Iso({x*32.0f,y*32.0f}));
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
		std::cout << "Mouse in Iso: (" << pos.x << "," << pos.y << "); ";
		float hoverXf = Iso2Flat({ (float)pos.x,(float)pos.y }).x  / 32;
		float hoverYf = Iso2Flat({ (float)pos.x,(float)pos.y }).y  / 32;

		int hoverX = (int)hoverXf;
		int hoverY = (int)hoverYf;
		std::cout << "Mouse in Flat: (" << hoverXf << "," << hoverYf << ");\n ";
		if (hoverX >= 0 && hoverY >= 0 && hoverX < width && hoverY < height)
		{
			tiles[hoverX][hoverY].SetHighlighted(true);
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