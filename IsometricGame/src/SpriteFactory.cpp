#include "SpriteFactory.h"
#include <exception>

SpriteFactory::SpriteFactory()
{
}

SpriteFactory::~SpriteFactory()
{
}

unsigned int SpriteFactory::LoadTexture(const std::string& texturePath)
{
	std::hash<std::string> hasher;
	unsigned int hash = hasher(texturePath);
	//unsigned int hash = std::hash<std::string>()(texturePath);
	if (textures.find(hash) == textures.end())
	{
		if (!textures[hash].loadFromFile(texturePath))
		{
			throw std::runtime_error("Could not find texture with path: " + texturePath);
		}
	}
	return hash;
}

sf::Sprite SpriteFactory::GetSprite(unsigned int hash)
{
	if (textures.find(hash) == textures.end())
	{
		throw std::runtime_error("Could not find texture with hash: " + hash);
	}
	return sf::Sprite(textures[hash]);
}