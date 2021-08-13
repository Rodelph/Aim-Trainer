#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Texture
{
	private:
		sf::Texture* texture;
		
		void initTexture();

	public :
		Texture();
		virtual ~Texture();
		
		sf::Texture* setTexture();

		void updateTexture();
		void renderTexture(sf::RenderTarget &target);
};