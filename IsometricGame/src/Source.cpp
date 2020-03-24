#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Tile.h"
#include "SpriteFactory.h"
#include "XmlWrapper.h"
// EP4, 1h14
float skewX =  400;
float skewY =  100;
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
	float p2_x = float(0.707f * p1_x - 0.707 * p1_y);
	float p2_y = float(-0.707f * p1_x + 0.707 * p1_y);
	float p3_x = p2_x;
	float p3_y = p2_y * 0.5f;
	float p4_x = p3_x + t_x * 32.0f - t_y * 32.0f -32 + skewX;
	float p4_y = p3_y + t_x * 16.0f + t_y * 16.0f +  skewY;
	return { p4_x,p4_y };
}
sf::Vector2f Iso2Flat(const sf::Vector2f& p)
{
	float a = 32.0f; float b = -32.0f; float c = 16.0f; float d = 16.0f;
	float det = (a * d - b * c);
	float t = d / det; float u = -b / det; float v = -c / det; float w = a / det;
	float xt = t * (p.x - skewX) + u * (p.y - skewY);
	float yt = v * (p.x - skewX) + w * (p.y - skewY);
	return { xt*32.0f , yt*32.0f };
}

int main()
{
	XmlWrapper map;
	map.LoadFile("resources/examplemap.tmx");
	const unsigned fieldWidth = std::stoi(map.GetAttribute("width"));
	const unsigned fieldHeight = std::atoi(map.GetAttribute("height").c_str());
	const float tileWidth = (float)std::stoi(map.GetAttribute("tilewidth"));
	const float tileHeight = (float)std::stoi(map.GetAttribute("tileheight"));
	const float tileHalfWidth = tileWidth / 2;
	const float tileHalfHeight = tileHeight / 2;

	sf::RenderWindow window(sf::VideoMode(800,600),"Isomeric Game");
	
	SpriteFactory factory;
	unsigned int tile = factory.LoadTexture("resources/iso_tile.png");
	unsigned int tile_hl = factory.LoadTexture("resources/iso_tile_hl.png");

	std::vector<std::vector<Tile>> tiles;
	tiles.reserve(fieldWidth);
	for (size_t x = 0; x < fieldWidth; x++)
	{
		std::vector<Tile> tileColumn;
		tileColumn.reserve(fieldHeight);
		for (size_t y = 0; y < fieldHeight; y++)
		{
			//Tile t(factory.GetSprite(tile), factory.GetSprite(tile_hl), Flat2Iso({x*32.0f,y*32.0f}));
			//sf::Vector2f test = Flat2Iso({ x * 32.0f,y * 32.0f });
			float xPos = x * tileHalfWidth  - y * tileHalfWidth  - tileHalfWidth + skewX;
			float yPos = y * tileHalfHeight + x * tileHalfHeight				 + skewY;
			Tile tile(factory.GetSprite(tile), factory.GetSprite(tile_hl), { xPos,yPos });
			tileColumn.push_back(tile);
		}
		tiles.push_back(tileColumn);
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

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		
		std::cout << "Mouse in Window coord: (" << mousePos.x << "," << mousePos.y << "); ";
		/*float hoverXf = (Iso2Flat({ (float)pos.x,(float)pos.y }).x ) / 32 ;
		float hoverYf = (Iso2Flat({ (float)pos.x,(float)pos.y }).y  ) / 32;
		int tileX = (int)hoverXf;
		int tileY= (int)hoverYf;*/
		int tileX = int( (mousePos.y - skewY) / tileHeight + (mousePos.x - skewX) / tileWidth  );
		int tileY = int(-(mousePos.x - skewX) / tileWidth  + (mousePos.y - skewY) / tileHeight );
		
		std::cout << "Mouse in IsoTile coord: (" << tileX << "," << tileY << ");\n ";
		
		if (tileX >= 0 && tileY >= 0 && tileX < (int)fieldWidth && tileY < (int)fieldHeight)
		{
			tiles[tileX][tileY].SetHighlighted(true);
		}

		for (size_t x = 0; x < fieldWidth; x++)
		{
			for (size_t y = 0; y < fieldHeight; y++)
			{
				tiles[x][y].Draw(window);
			}
		}

		window.display();
	}
	return 0;
}