#include "Game.h"


/// 
/// Initialization functions that will initialize everything for the game
/// 

void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 200;

	this->enemySpawnTimerMaxCirc = 1.f;
	this->enemySpawnTimerCirc = this->enemySpawnTimerMaxCirc;
	this->maxEnemiesCirc = 1;

	this->mouseHeld = false;
	this->endGame = false;
	this->pauseGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Hit me Up !", sf::Style::Titlebar | sf::Style::Close);
	this->window->setVerticalSyncEnabled(false);
	this->window->setFramerateLimit(61);
}

void Game::initEnemiesCirc()
{
	this->enemyCircle.setPosition(100.f, 100.f);
	this->enemyCircle.setRadius(20.f);
	this->enemyCircle.setOutlineColor(sf::Color::Black);
	this->enemyCircle.setOutlineThickness(10.f);
	this->enemyCircle.setScale(0.5f, 0.5f);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("src/Fonts/Dosis-Light.ttf")) { std::cout << "Info::GAME::InitFonts:: Font not loaded !" << std::endl; }
	else { this->font.loadFromFile("src/Fonts/Dosis-Light.ttf");}
}

void Game::initPointStats()
{
	this->uiPointStats.setFont(this->font);
	this->uiPointStats.setCharacterSize(24);
	this->uiPointStats.setFillColor(sf::Color::Black);
	this->uiPointStats.setPosition(0, 30);
	this->uiPointStats.setString("NONE");
}

void Game::initLevelStats()
{
	this->uiLevelStats.setFont(this->font);
	this->uiLevelStats.setCharacterSize(24);
	this->uiLevelStats.setFillColor(sf::Color::Black);
	this->uiLevelStats.setPosition(0, 60);
	this->uiLevelStats.setString("NONE");
}

void Game::initFpsStats()
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
	this->hpBorder.setSize(sf::Vector2f(200.f, 20.f));
	this->hpBorder.setOutlineColor(sf::Color::Black);
	this->hpBorder.setOutlineThickness(1.f);
}

void Game::initRestart()
{
	this->uiRestart.setFont(this->font);
	this->uiRestart.setPosition(330, 200);
	this->uiRestart.setCharacterSize(24);
	this->uiRestart.setFillColor(sf::Color::Black);
}

void Game::initScore()
{
	this->uiScore.setFont(this->font);
	this->uiScore.setPosition(330, 300);
	this->uiScore.setCharacterSize(24);
	this->uiScore.setFillColor(sf::Color::Black);
}

void Game::initQuit()
{
	this->uiQuit.setFont(this->font);
	this->uiQuit.setPosition(330, 400);
	this->uiQuit.setFillColor(sf::Color::Black);
	this->uiQuit.setCharacterSize(24);
}

void Game::initAudio() { this->audGame = new AudioGame(); }

/// 
/// Update functions that will be used to update the game
/// 

void Game::updateEnemyCircle()
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
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(50.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 1:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(40.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 2:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(30.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f); 
			break;
	
		case 3:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(20.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 4:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(15.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 5:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(10.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;
	}

	//Spawn, the enemies
	this->enemiesCirc.push_back(this->enemyCircle);
}

void Game::updateHpBar() { this->hpBar.setSize(sf::Vector2f(this->health, 20)); }

void Game::updateEnemies()
{
	//Update the timer for enemy spawning
	if (this->enemiesCirc.size() < this->maxEnemiesCirc)
	{
		if (this->enemySpawnTimerCirc >= this->enemySpawnTimerMaxCirc)
		{
			//Spawn the enemy and reset the timer
			this->updateEnemyCircle();
			this->enemySpawnTimerCirc = 10.f;
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
			if (this->enemyCircle.getRadius() == 50.f) { this->health -= 5; }

			if (this->enemyCircle.getRadius() == 40.f) { this->health -= 10; }

			if (this->enemyCircle.getRadius() == 30.f) { this->health -= 20; }

			if (this->enemyCircle.getRadius() == 20.f) { this->health -= 30; }

			if (this->enemyCircle.getRadius() == 15.f) { this->health -= 50; }

			if (this->enemyCircle.getRadius() == 10.f) { this->health -= 70; }
		}
	}

	//Check if clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;

			for (size_t i = 0; i < this->enemiesCirc.size() && deleted == false; i++)
			{
				if (this->enemiesCirc[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Deleting enemies and point system
					if (this->enemyCircle.getRadius() == 50.f){ this->points += 5; this->health += 2.f; if (this->health >= 200.f) this->health = 200.f;}
					
					else if (this->enemyCircle.getRadius() == 40.f){ this->points += 10; this->health += 5.f; if (this->health >= 200.f) this->health = 200.f;}
					
					else if (this->enemyCircle.getRadius() == 30.f){ this->health += 10; this->points += 20.f; if (this->health >= 200.f) this->health = 200.f;}
					
					else if (this->enemyCircle.getRadius() == 20.f) { this->health += 20; this->points += 30.f; if (this->health >= 200.f) this->health = 200.f;}
					
					else if (this->enemyCircle.getRadius() == 15.f){ this->health += 30; this->points += 50.f; if (this->health >= 200.f) this->health = 200.f;}
					
					else if (this->enemyCircle.getRadius() == 10.f){ this->hpBar.setSize(sf::Vector2f(200, 20)); this->points += 100; if (this->health >= 200.f) this->health = 200.f;}
					 
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
		Mouse position relative to window (Vector2i)
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updatePointStats()
{
	std::stringstream ssStats;
	ssStats << "Points : " << this->points << "\n";
	this->uiPointStats.setString(ssStats.str());
}

void Game::updateFpsStats()
{
	std::stringstream ssFps;
	this->time = this->clock.getElapsedTime();
	ssFps << "FPS : " << (int)(1.0f / this->time.asSeconds()) << "\n";
	this->uiFpsStats.setString(ssFps.str());
	this->clock.restart().asSeconds();
}

void Game::updateLevelStats()
{
	if (this->points < 400) 
	{ 
		std::stringstream ssLevel;
		ssLevel << "Level : " << 1 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 400)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 2 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 800)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 3 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 1200)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 4 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 1600)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 5 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 2000)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 6 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 2400)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 7 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 2800)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 8 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
}

void Game::updateRestart()
{
	std::stringstream restart;
	restart << "Restart\n";
	this->uiRestart.setString(restart.str());
}

void Game::updateScore()
{
	std::stringstream score;
	score << "You final score is : " << this->points << "\n";
	this->uiScore.setString(score.str());
}

void Game::updateQuit() 
{ 
	std::stringstream quit;
	quit << "Quit\n";
	this->uiQuit.setString(quit.str());
}

void Game::updateSpawn()
{
	if (this->points >=  400) this->maxEnemiesCirc = 2;
	if (this->points >=  800) this->maxEnemiesCirc = 3;
	if (this->points >= 1200) this->maxEnemiesCirc = 4;
	if (this->points >= 1600) this->maxEnemiesCirc = 5;
	if (this->points >= 2000) this->maxEnemiesCirc = 6;
	if (this->points >= 2400) this->maxEnemiesCirc = 7;
	if (this->points >= 2800) this->maxEnemiesCirc = 8;
}

void Game::update()
{
	this->pollEvents();
	if(!this->pauseGame && !this->endGame)
	{
		this->updateMousePos();
		this->updateEnemies();
		this->updateHpBar();
		this->updateSpawn();
		this->updatePointStats();
		this->updateFpsStats();
		this->updateLevelStats();
	}

	if (this->pauseGame)
	{
		audGame->stopBGM();
		this->window->setFramerateLimit(1);
		this->updateRestart();
		this->updateScore();
		this->updateQuit();
	}
	
	if (this->hpBar.getSize().x <= 0) { this->pauseGame = true; }
}

/// 
/// Render functions that will be used to render the game
/// 

void Game::renderPointStats(sf::RenderTarget& target) { target.draw(this->uiPointStats); }

void Game::renderFpsStats(sf::RenderTarget& target) { target.draw(this->uiFpsStats); }

void Game::renderEnemeiesCirc(sf::RenderTarget& target){ for (auto& e : this->enemiesCirc) { target.draw(e); } }

void Game::renderLevelStats(sf::RenderTarget& target) { target.draw(this->uiLevelStats); }

void Game::rednderHpBar(sf::RenderTarget& target){ target.draw(this->hpBorder); target.draw(this->hpBar); }

void Game::renderQuit(sf::RenderTarget& target) { target.draw(this->uiQuit); }

void Game::renderRestart(sf::RenderTarget& target) { target.draw(this->uiRestart); }

void Game::renderScore(sf::RenderTarget& target) { target.draw(this->uiScore); }

void Game::render()
{
	/*Renders the game object by : 
		Clearing the old frame
		Rendering objects
		Displaying them
	*/
	this->window->clear(sf::Color(115, 147, 161, 255));
	this->renderEnemeiesCirc(*this->window);
	this->rednderHpBar(*this->window);
	this->renderFpsStats(*this->window);
	this->renderPointStats(*this->window);
	this->renderLevelStats(*this->window);
	this->renderRestart(*this->window);
	this->renderScore(*this->window);
	this->renderQuit(*this->window);
	this->window->display();
}

/// 
/// Game States, poll events, constructor and destructor
/// 

//Accessors
           
const bool Game::running() const { return this->window->isOpen(); }

const bool Game::getEndGame() const { return this->endGame; }

const bool Game::getPauseGame() const { return this->pauseGame; }

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

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFont();
	this->initQuit();
	this->initRestart();
	this->initScore();
	this->initPointStats();
	this->initFpsStats();
	this->initLevelStats();
	this->initAudio();
	this->initHpBar();
	this->initEnemiesCirc();
}

Game::~Game() { delete this->window; this->audGame->~AudioGame(); }