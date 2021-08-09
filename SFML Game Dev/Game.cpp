#include "Game.h"

//Private fctions
void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Hit me Up !", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

//Constructors and destructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
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

Game::~Game()
{
	delete this->window;
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

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
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
		this->enemies[i].move(0.f, 1.f);
		bool deleted = false;

		//Check if clicked on
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;
				this->points += 1;
				std::cout << this->points << std::endl;
			}
		}

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}

		if(deleted)
			this->enemies.erase(this->enemies.begin() + i);
	}
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePos();
	this->updateEnemies();
}

void Game::render()
{
	/*Renders the game object by : 
		Clearing the old frame
		Rendering objects
		Displaying them
	*/
	this->window->clear(sf::Color(245, 245, 220, 255));
	this->renderEnemies();
	this->window->display();
}