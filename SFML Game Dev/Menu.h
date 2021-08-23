#pragma once

#include <SFML/Graphics.hpp>
#include "IOFile.h"

#define MAX_NUMBER_ITEMS 3

class Menu
{
	private:
		int selectedItemIndex;
		IOFile *iofile = new IOFile();

	public :
		Menu(float width, float height);
		virtual ~Menu();

		sf::Font font;
		sf::Text menu[MAX_NUMBER_ITEMS];

		void MoveUp();
		void MoveDown();
		void renderMenu(sf::RenderTarget& target);
};