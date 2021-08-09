#include "Game.h"

//Private fctions
void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 50;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Hit me Up !", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(75);
}

//Constructors and destructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFont();
	this->initText();
	this->initEnemies();	
}

void Game::initEnemies()
{
	this->enemy.setPosition(100.f, 100.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
	this->enemy.setScale(0.5f, 0.5f);
}

void Game::initFont()
{
	if (this->font.loadFromFile("src/Fonts/Dosis-Light.ttf"))
	{
		std::cout << "Info::GAME::InitFonts:: font loaded !" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::Black);
	this->uiText.setPosition(0, 0);
	this->uiText.setString("NONE");
}

Game::~Game()
{
	delete this->window;
}

void Game::spawnEnemy()
{
	//Spawns enemies and sets their color and positions 
	//	   Sets a random position
	// 	   Sets a random color
	// 	   Adds enemy to the vector
	//	   Moves the enemies
	//	   Removes the edge of the enemies from the screen

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//Spaw, the enemies
	this->enemies.push_back(this->enemy);

	//Remove the enemies
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Public functions
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Game::updateEnemies()
{
	//Update the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Your HP is : " << this->health << std::endl;
		}
	}
	//Check if clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gain points
					this->points += 1;
					std::cout <<"Your have a total of : " << this->points << " points !!" << std::endl;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateMousePos()
{
	/*
	Updates the mouse positions :
		Mouse position relateve to window (Vector2i)
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points : " << this->points << "\n"
		<< "Health : " << this->health << "\n";
	this->uiText.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::update()
{
	this->pollEvents();
	if(!this->endGame)
	{
		this->updateMousePos();
		this->updateText();
		this->updateEnemies();
	}

	if (this->health == 0)
	{
		std::cout << "You lost !!" << std::endl;
		this->endGame = true;
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	/*Renders the game object by : 
		Clearing the old frame
		Rendering objects
		Displaying them
	*/
	this->window->clear(sf::Color(245, 245, 220, 255));
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}