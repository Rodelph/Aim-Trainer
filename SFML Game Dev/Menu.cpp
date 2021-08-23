#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!this->font.loadFromFile(this->iofile->getFontDir())) { std::cout << this->iofile->getFontError() << std::endl; }
	else { this->font.loadFromFile(this->iofile->getFontDir()); }
}

Menu::~Menu() { delete this->menu; }

void Menu::MoveUp()
{

}

void Menu::MoveDown()
{

}