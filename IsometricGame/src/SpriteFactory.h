#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class SpriteFactory
{
public:
	SpriteFactory();
	~SpriteFactory();
	unsigned int LoadTexture(const std::string& texturePath);
	sf::Sprite GetSprite(unsigned int hash);
private:
	std::map<unsigned,sf::Texture> textures;
};