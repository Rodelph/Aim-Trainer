#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 200;

	this->enemySpawnTimerMaxRect = 1.f;
	this->enemySpawnTimerRect = this->enemySpawnTimerMaxRect;
	this->maxEnemiesRect = 1;

	this->enemySpawnTimerMaxCirc = 1.f;
	this->enemySpawnTimerCirc = this->enemySpawnTimerMaxCirc;
	this->maxEnemiesCirc = 1;

	this->mouseHeld = false;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Hit me Up !", sf::Style::Titlebar | sf::Style::Close);
	this->window->setVerticalSyncEnabled(true);
}

void Game::initEnemiesRect()
{
	this->enemyRect.setPosition(100.f, 100.f);
	this->enemyRect.setSize(sf::Vector2f(100.f, 100.f));
	this->enemyRect.setOutlineColor(sf::Color::Green);
	this->enemyRect.setOutlineThickness(1.f);
	this->enemyRect.setScale(0.5f, 0.5f);
}

void Game::initEnemiesCirc()
{
	this->enemyCircle.setPosition(100.f, 100.f);
	this->enemyCircle.setRadius(20.f);
	this->enemyCircle.setOutlineColor(sf::Color::Black);
	this->enemyCircle.setOutlineThickness(1.f);
	this->enemyCircle.setScale(0.5f, 0.5f);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("src/Fonts/Dosis-Light.ttf"))
		std::cout << "Info::GAME::InitFonts:: Font not loaded !" << std::endl;
	else
		this->font.loadFromFile("src/Fonts/Dosis-Light.ttf");
}

void Game::initTextStats()
{
	this->uiTextStats.setFont(this->font);
	this->uiTextStats.setCharacterSize(24);
	this->uiTextStats.setFillColor(sf::Color::Black);
	this->uiTextStats.setPosition(0, 30);
	this->uiTextStats.setString("NONE");
}

void Game::initTextFps()
{
	this->uiFpsStats.setFont(this->font);
	this->uiFpsStats.setCharacterSize(18);
	this->uiFpsStats.setFillColor(sf::Color::Black);
	this->uiFpsStats.setPosition(735, 0);
	this->uiFpsStats.setString("NONE");
}

void Game::initHpBar()
{
	this->hpBar.setPosition(2, 5);
	this->hpBar.setSize(sf::Vector2f(200.f, 40.f));
	this->hpBar.setFillColor(sf::Color::Red);
	
	this->hpBorder.setPosition(2, 5);
	this->hpBorder.setSize(sf::Vector2f(200.f, 40.f));
	this->hpBorder.setOutlineColor(sf::Color::Black);
	this->hpBorder.setOutlineThickness(1.f);
}
void Game::initAudio() { this->audGame = new AudioGame(); }

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFont();
	this->initTextStats();
	this->initTextFps();
	this->initAudio();
	this->initHpBar();
	this->initEnemiesRect();
	this->initEnemiesCirc();
}

Game::~Game()
{
	delete this->window;
}

void Game::spawnEnemyRect()
{
	//Spawns enemies and sets their color and positions 
	//	   Sets a random position
	// 	   Sets a random color
	// 	   Adds enemy to the vector
	//	   Moves the enemies
	//	   Removes the edge of the enemies from the screen

	this->enemyRect.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyRect.getSize().x)),
		0.f
	);

	int type = rand() % 5;
	switch (type)
	{
		case 0:
			this->enemyRect.setFillColor(sf::Color::Green);
			this->enemyRect.setSize(sf::Vector2f(100.f, 100.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 1:
			this->enemyRect.setFillColor(sf::Color::Red);
			this->enemyRect.setSize(sf::Vector2f(50.f, 50.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 2:
			this->enemyRect.setFillColor(sf::Color::Cyan);
			this->enemyRect.setSize(sf::Vector2f(30.f, 30.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;
		case 3:
			this->enemyRect.setFillColor(sf::Color::Blue);
			this->enemyRect.setSize(sf::Vector2f(20.f, 20.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 4:
			this->enemyRect.setFillColor(sf::Color::Magenta);
			this->enemyRect.setSize(sf::Vector2f(15.f, 15.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 5:
			this->enemyRect.setFillColor(sf::Color::White);
			this->enemyRect.setSize(sf::Vector2f(10.f, 10.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;
	}

	//Spaw, the enemies
	this->enemiesRect.push_back(this->enemyRect);
}

void Game::spawnEnemyCircle()
{

//Spawns enemies and sets their color and positions 
//	   Sets a random position
// 	   Sets a random color
// 	   Adds enemy to the vector
//	   Moves the enemies
//	   Removes the edge of the enemies from the screen

	this->enemyCircle.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyCircle.getRadius())),
		0.f
	);

	int type = rand() % 5;
	switch (type)
	{
		case 0:
			this->enemyCircle.setFillColor(sf::Color::Green);
			this->enemyCircle.setRadius(50.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 1:
			this->enemyCircle.setFillColor(sf::Color::Red);
			this->enemyCircle.setRadius(40.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 2:
			this->enemyCircle.setFillColor(sf::Color::Cyan);
			this->enemyCircle.setRadius(30.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f); 
			break;
	
		case 3:
			this->enemyCircle.setFillColor(sf::Color::Blue);
			this->enemyCircle.setRadius(20.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 4:
			this->enemyCircle.setFillColor(sf::Color::Magenta);
			this->enemyCircle.setRadius(15.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 5:
			this->enemyCircle.setFillColor(sf::Color::White);
			this->enemyCircle.setRadius(10.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;
	}
	//Spaw, the enemies
	this->enemiesCirc.push_back(this->enemyCircle);
}

//Fix hp bar
void Game::updateHpBar()
{
	float healthVal = this->health;
	this->hpBorder.setSize(sf::Vector2f(200, 20));
	this->hpBar.setSize(sf::Vector2f(this->health, 20));
	if (this->hpBar.getSize().x > 200) { this->hpBar.setSize(sf::Vector2f(200, 20)); }
}

//Accessors
const bool Game::running() const { return this->window->isOpen(); }

const bool Game::getEndGame() const { return this->endGame; }

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
				if (this->ev.key.code == sf::Keyboard::Escape) { this->window->close(); }
				break;
		}
	}
}

void Game::updateEnemies()
{
	//Update the timer for enemy spawning
	if (this->enemiesRect.size() < this->maxEnemiesRect)
	{
		if (this->enemySpawnTimerRect >= this->enemySpawnTimerMaxRect)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemyRect();
			this->enemySpawnTimerRect = 0.f;
		}
		else
			this->enemySpawnTimerRect += 1.f;
	}

	//Move the enemies
	for (int i = 0; i < this->enemiesRect.size(); i++)
	{
		bool deleted = false;
		this->enemiesRect[i].move(0.f, 5.f);
		if (this->enemiesRect[i].getPosition().y > this->window->getSize().y)
		{
			this->enemiesRect.erase(this->enemiesRect.begin() + i);

			//Hp loss
			if (this->enemyRect.getFillColor() == sf::Color::Green) { this->health -= 5; }

			if (this->enemyRect.getFillColor() == sf::Color::Red) { this->health -= 10; }

			if (this->enemyRect.getFillColor() == sf::Color::Cyan) { this->health -= 20; }

			if (this->enemyRect.getFillColor() == sf::Color::Blue) { this->health -= 30; }

			if (this->enemyRect.getFillColor() == sf::Color::White) { this->health -= 50; }

			if (this->enemyRect.getFillColor() == sf::Color::Magenta) { this->health -= 70; }
		}
	}

	if (this->enemiesCirc.size() < this->maxEnemiesCirc)
	{
		if (this->enemySpawnTimerCirc >= this->enemySpawnTimerMaxCirc)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemyCircle();
			this->enemySpawnTimerCirc = 100.f;
		}
		else
			this->enemySpawnTimerCirc += 1.f;
	}

	//Move the enemies
	for (int i = 0; i < this->enemiesCirc.size(); i++)
	{
		bool deleted = false;
		this->enemiesCirc[i].move(0.f, 5.f);
		if (this->enemiesCirc[i].getPosition().y > this->window->getSize().y)
		{
			this->enemiesCirc.erase(this->enemiesCirc.begin() + i);
			//Hp loss
			if (this->enemyCircle.getFillColor() == sf::Color::Green) { this->health -= 5; }

			if (this->enemyCircle.getFillColor() == sf::Color::Red) { this->health -= 10; }

			if (this->enemyCircle.getFillColor() == sf::Color::Cyan) { this->health -= 20; }

			if (this->enemyCircle.getFillColor() == sf::Color::Blue) { this->health -= 30; }

			if (this->enemyCircle.getFillColor() == sf::Color::White) { this->health -= 50; }

			if (this->enemyCircle.getFillColor() == sf::Color::Magenta) { this->health -= 70; }
		}
	}

	//Check if clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemiesRect.size() && deleted == false; i++)
			{
				if (this->enemiesRect[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Deleting enemies and point system
					if (this->enemiesRect[i].getFillColor() == sf::Color::Green) { this->health += 2; this->points += 5; }
					
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Red) { this->health += 5; this->points += 10; }
					
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Blue) { this->health += 10; this->points += 20; }
					
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Cyan) { this->health += 20; this->points += 30; }
					
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Magenta) { this->health += 30; this->points += 50; }
					
					else if (this->enemiesRect[i].getFillColor() == sf::Color::White) { this->hpBar.setSize(sf::Vector2f(200, 20)); this->points += 100; }
					
					deleted = true;

					this->enemiesRect.erase(this->enemiesRect.begin() + i);

					//Sfx when u hit a target
					this->audGame->playSFX();
				}
			}

			for (size_t i = 0; i < this->enemiesCirc.size() && deleted == false; i++)
			{
				if (this->enemiesCirc[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Deleting enemies and point system
					if (this->enemiesCirc[i].getFillColor() == sf::Color::Green){ this->points += 5; this->health += 2; }
					
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Red){ this->points += 10; this->health += 5; }
					
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Blue){ this->health += 10; this->points += 20; }
					
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Cyan){ this->health += 20; this->points += 30; }
					
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Magenta){ this->health += 30; this->points += 50; }
					
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::White){ this->hpBar.setSize(sf::Vector2f(200, 20)); this->points += 100; }
					 
					deleted = true;

					this->enemiesCirc.erase(this->enemiesCirc.begin() + i);

					//Sfx when u hit a target
					this->audGame->playSFX();
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

void Game::updateTextStats()
{
	std::stringstream ssStats;
	ssStats << "Points : " << this->points << "\n";
	this->uiTextStats.setString(ssStats.str());
}

void Game::updateTextFps()
{
	std::stringstream ssFps;
	this->time = this->clock.getElapsedTime();
	ssFps << "FPS : " << (int)(1.0f / this->time.asSeconds()) << "\n";
	this->uiFpsStats.setString(ssFps.str());
	this->clock.restart().asSeconds();
}

void Game::update()
{
	this->pollEvents();
	if(!this->endGame)
	{
		this->updateMousePos();
		this->updateEnemies();
		this->updateHpBar();
		this->updateTextStats();
		this->updateTextFps();
	}

	if (this->hpBar.getSize().x <= 0)
	{
		std::cout << "You lost !!" << std::endl;
		this->endGame = true;
	}
}

void Game::renderTextStats(sf::RenderTarget& target) { target.draw(this->uiTextStats); }

void Game::renderTextFps(sf::RenderTarget& target) { target.draw(this->uiFpsStats); }

void Game::renderEnemiesRect(sf::RenderTarget& target){ for (auto& e : this->enemiesRect) { target.draw(e); } }

void Game::renderEnemeiesCirc(sf::RenderTarget& target){ for (auto& e : this->enemiesCirc) { target.draw(e); } }

void Game::rednderHpBar(sf::RenderTarget& target){ target.draw(this->hpBorder); target.draw(this->hpBar); }

void Game::render()
{
	/*Renders the game object by : 
		Clearing the old frame
		Rendering objects
		Displaying them
	*/
	this->window->clear(sf::Color(245, 245, 220, 255));
	this->renderEnemiesRect(*this->window);
	this->renderEnemeiesCirc(*this->window);
	this->rednderHpBar(*this->window);
	this->renderTextFps(*this->window);
	this->renderTextStats(*this->window);
	this->window->display();
}