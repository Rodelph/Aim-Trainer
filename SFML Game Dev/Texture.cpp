#include "Texture.h"

void Texture::initTexture()
{
	if (!this->texture->loadFromFile("src/Texture/hitTarget.png"))
		std::cout << "Info::GAME::InitTexture:: Texture not loaded !" << std::endl;
	else
		this->texture->loadFromFile("src/Texture/hitTarget.png");
}

Texture::Texture()
{
	this->initTexture();
}

Texture::~Texture()
{
	delete this->texture;
	this->texture = nullptr;
}

sf::Texture* Texture::setTexture()
{
	this->texture->loadFromFile("src/Texture/hitTarget.png");
	return this->texture;
}